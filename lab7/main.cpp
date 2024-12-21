#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <memory>
#include <atomic>
#include <chrono>
#include <random>
#include "NPC.h"
#include "NPCFactory.h"

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 20;
const int GAME_DURATION = 30; 

std::vector<std::shared_ptr<NPC>> npcList;
std::shared_mutex npcListMutex;
std::mutex coutMutex;

void createNPCs() {
    for (int i = 0; i < 50; ++i) {
        auto npc = NPCFactory::createRandomNPC(i);
        if (npc) {
            std::unique_lock<std::shared_mutex> lock(npcListMutex);
            npcList.push_back(npc);
        }
    }

    {
        std::lock_guard<std::mutex> coutLock(coutMutex);
        std::cout << "Created NPCs:\n";
        for (const auto& npc : npcList) {
            std::cout << npc->getType() << " " << npc->getId()
                      << " at (" << npc->getX() << ", " << npc->getY() << ")\n";
        }
    }
}

void moveNPCs(std::atomic<bool>& running, std::mutex& battleQueueMutex,
              std::vector<std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>>>& battleQueue) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> distDir(-1, 1);

    {
        std::lock_guard<std::mutex> coutLock(coutMutex);
        std::cout << "Movement thread started\n";
    }

    while (running.load()) {
        {
            std::shared_lock<std::shared_mutex> npcListLock(npcListMutex);

            for (auto& npc : npcList) {
                std::unique_lock<std::shared_mutex> npcLock(npc->getMutex());
                if (!npc->isAlive()) continue;

                NPCStats stats = npc->getStats();
                int dx = distDir(rng) * stats.moveDistance;
                int dy = distDir(rng) * stats.moveDistance;
                int newX = npc->getX() + dx;
                int newY = npc->getY() + dy;
                npc->setPosition(newX, newY);
            }
        }

        {
            std::shared_lock<std::shared_mutex> npcListLock(npcListMutex);
            for (size_t i = 0; i < npcList.size(); ++i) {
                auto npc1 = npcList[i];
                std::shared_lock<std::shared_mutex> lock1(npc1->getMutex());
                if (!npc1->isAlive()) continue;

                for (size_t j = i + 1; j < npcList.size(); ++j) {
                    auto npc2 = npcList[j];
                    std::shared_lock<std::shared_mutex> lock2(npc2->getMutex());
                    if (!npc2->isAlive()) continue;

                    bool canBattle = npc1->canAttack(npc2);

                    if (canBattle) {
                        int dx = npc1->getX() - npc2->getX();
                        int dy = npc1->getY() - npc2->getY();
                        int distanceSquared = dx * dx + dy * dy;
                        int killDistance = npc1->getStats().killDistance;
                        if (distanceSquared <= killDistance * killDistance) {
                            {
                                std::lock_guard<std::mutex> queueLock(battleQueueMutex);
                                battleQueue.push_back({npc1, npc2});
                            }
                        }
                    }
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    {
        std::lock_guard<std::mutex> coutLock(coutMutex);
        std::cout << "Movement thread ended\n";
    }
}

void battleNPCs(std::atomic<bool>& running, std::mutex& battleQueueMutex,
                std::vector<std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>>>& battleQueue) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> diceRoll(1, 6);

    {
        std::lock_guard<std::mutex> coutLock(coutMutex);
        std::cout << "Battle thread started\n";
    }

    while (running.load() || !battleQueue.empty()) {
        std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>> battlePair;
        bool hasBattle = false;

        {
            std::lock_guard<std::mutex> queueLock(battleQueueMutex);
            if (!battleQueue.empty()) {
                battlePair = battleQueue.back();
                battleQueue.pop_back();
                hasBattle = true;
            }
        }

        if (hasBattle) {
            auto npc1 = battlePair.first;
            auto npc2 = battlePair.second;

            std::scoped_lock lock(npc1->getMutex(), npc2->getMutex());

            if (!npc1->isAlive() || !npc2->isAlive()) continue;

            int attack = diceRoll(rng);
            int defense = diceRoll(rng);

            if (attack > defense) {
                npc2->setAlive(false);

                std::lock_guard<std::mutex> coutLock(coutMutex);
                std::cout << npc1->getType() << " " << npc1->getId() << " defeated "
                          << npc2->getType() << " " << npc2->getId() << std::endl;
            } else {
                npc1->setAlive(false);

                std::lock_guard<std::mutex> coutLock(coutMutex);
                std::cout << npc2->getType() << " " << npc2->getId() << " survived attack from "
                          << npc1->getType() << " " << npc1->getId() << std::endl;
            }
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    {
        std::lock_guard<std::mutex> coutLock(coutMutex);
        std::cout << "Battle thread ended\n";
    }
}

void displayMap(std::atomic<bool>& running) {
    while (running.load()) {
        {
            std::lock_guard<std::mutex> coutLock(coutMutex);
            std::cout << "==============================\n";
        }

        char map[MAP_HEIGHT][MAP_WIDTH];
        for (int i = 0; i < MAP_HEIGHT; ++i)
            for (int j = 0; j < MAP_WIDTH; ++j)
                map[i][j] = '.';

        {
            std::shared_lock<std::shared_mutex> npcListLock(npcListMutex);

            for (const auto& npc : npcList) {
                std::shared_lock<std::shared_mutex> npcLock(npc->getMutex());
                if (!npc->isAlive()) continue;

                int x = npc->getX();
                int y = npc->getY();

                char symbol = '?';
                if (npc->getType() == "Dragon") symbol = 'D';
                else if (npc->getType() == "Bull") symbol = 'B';
                else if (npc->getType() == "Toad") symbol = 'T';

                if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
                    map[y][x] = symbol;
                }
            }
        }

        {
            std::lock_guard<std::mutex> coutLock(coutMutex);
            for (int i = 0; i < MAP_HEIGHT; ++i) {
                for (int j = 0; j < MAP_WIDTH; ++j) {
                    std::cout << map[i][j];
                }
                std::cout << std::endl;
            }
            std::cout << std::flush;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    std::cout << "Program started\n";
    createNPCs();

    std::atomic<bool> running(true);
    std::mutex battleQueueMutex;
    std::vector<std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>>> battleQueue;

    std::thread movementThread(moveNPCs, std::ref(running), std::ref(battleQueueMutex), std::ref(battleQueue));
    std::thread battleThread(battleNPCs, std::ref(running), std::ref(battleQueueMutex), std::ref(battleQueue));

    auto startTime = std::chrono::steady_clock::now();

    while (running.load()) {
        displayMap(running);

        auto currentTime = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

        if (elapsed >= GAME_DURATION) {
            running.store(false);
            break;
        }
    }

    movementThread.join();
    battleThread.join();

    {
        std::lock_guard<std::mutex> coutLock(coutMutex);
        std::cout << "\nGame over! Surviving NPCs:\n";
        std::shared_lock<std::shared_mutex> npcListLock(npcListMutex);

        for (const auto& npc : npcList) {
            std::shared_lock<std::shared_mutex> npcLock(npc->getMutex());
            if (npc->isAlive()) {
                std::cout << npc->getType() << " " << npc->getId()
                          << " at (" << npc->getX() << ", " << npc->getY() << ")\n";
            }
        }
    }

    std::cout << "Program ended\n";
    return 0;
}

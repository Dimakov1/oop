#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <sstream>
#include <memory>
#include <locale>

#ifdef _WIN32
#include <codecvt>
#endif

#include "Subject.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"
#include "NPC.h"
#include "NPCFactory.h"

int main() {
    std::locale::global(std::locale(""));

    auto consoleLogger = std::make_shared<ConsoleLogger>();
    auto fileLogger = std::make_shared<FileLogger>("log.txt");
    Subject battleLogger;
    battleLogger.attach(consoleLogger);
    battleLogger.attach(fileLogger);

    const int MAX_NPCS = 100;
    std::array<std::shared_ptr<NPC>, MAX_NPCS> npcArray;
    int npcCount = 0;

    std::string command;
    while (std::getline(std::cin, command)) {
        if (command.empty()) continue;

        command.erase(0, command.find_first_not_of(" \t"));

        if (command.find("Добавить") == 0) {

            std::istringstream iss(command);
            std::string cmd, type;
            iss >> cmd >> type;

            std::map<std::string, std::string> params;
            std::string token;
            while (iss >> token) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string key = token.substr(0, pos);
                    std::string value = token.substr(pos + 1);
                    params[key] = value;
                }
            }

            if (params.find("x") == params.end() || params.find("y") == params.end() || params.find("имя") == params.end()) {
                std::cout << "Неверный формат команды Добавить." << std::endl;
                continue;
            }

            int x = std::stoi(params["x"]);
            int y = std::stoi(params["y"]);
            std::string name = params["имя"];

            if (x < 0 || x > 500 || y < 0 || y > 500) {
                std::cout << "Координаты вне диапазона." << std::endl;
                continue;
            }

            bool nameExists = false;
            for (int i = 0; i < npcCount; ++i) {
                if (npcArray[i]->getName() == name) {
                    nameExists = true;
                    break;
                }
            }
            if (nameExists) {
                std::cout << "NPC с таким именем уже существует." << std::endl;
                continue;
            }

            if (npcCount >= MAX_NPCS) {
                std::cout << "Достигнут максимальный размер массива NPC." << std::endl;
                continue;
            }

            auto npc = NPCFactory::createNPC(type, name, x, y);
            if (npc) {
                npc->attach(consoleLogger);
                npc->attach(fileLogger);
                npcArray[npcCount++] = npc;
                std::cout << "NPC " << type << " " << name << " добавлен." << std::endl;
            }
            else {
                std::cout << "Неизвестный тип NPC." << std::endl;
            }

        }
        else if (command.find("Сохранить") == 0) {
            std::istringstream iss(command);
            std::string cmd, in, file, filename;
            iss >> cmd >> in >> file >> filename;

            if (filename.empty()) {
                std::cout << "Неверный формат команды Сохранить." << std::endl;
                continue;
            }

            NPCFactory::saveToFile(filename, std::vector<std::shared_ptr<NPC>>(npcArray.begin(), npcArray.begin() + npcCount));
            std::cout << "Данные сохранены в файл " << filename << std::endl;

        }
        else if (command.find("Бой") == 0) {
            std::istringstream iss(command);
            std::string cmd, radiusStr;
            iss >> cmd >> radiusStr;
            auto pos = radiusStr.find('=');
            if (pos == std::string::npos) {
                std::cout << "Неверный формат команды Бой." << std::endl;
                continue;
            }
            int radius = std::stoi(radiusStr.substr(pos + 1));

            for (int i = 0; i < npcCount; ++i) {
                auto npc1 = npcArray[i];
                if (!npc1->isAlive()) continue;
                for (int j = i + 1; j < npcCount; ++j) {
                    auto npc2 = npcArray[j];
                    if (!npc2->isAlive()) continue;

                    int dx = npc1->getX() - npc2->getX();
                    int dy = npc1->getY() - npc2->getY();
                    int distanceSquared = dx * dx + dy * dy;

                    if (distanceSquared <= radius * radius) {
                        npc1->interactWith(npc2.get(), battleLogger); 
                        npc2->interactWith(npc1.get(), battleLogger); 
                    }
                }
            }
            std::cout << "Бой завершен." << std::endl;

        }
        else if (command.find("Печать") == 0) {
            for (int i = 0; i < npcCount; ++i) {
                auto npc = npcArray[i];
                if (npc->isAlive()) {
                    std::cout << "NPC: " << npc->getType() << ", Имя: " << npc->getName()
                        << ", x=" << npc->getX() << ", y=" << npc->getY() << std::endl;
                }
            }
        }
        else if (command.find("Загрузить") == 0) {
            std::istringstream iss(command);
            std::string cmd, from, file, filename;
            iss >> cmd >> from >> file >> filename;

            if (filename.empty()) {
                std::cout << "Неверный формат команды Загрузить." << std::endl;
                continue;
            }

            auto loadedNPCs = NPCFactory::loadFromFile(filename);
            for (const auto& npc : loadedNPCs) {
                if (npcCount >= MAX_NPCS) {
                    std::cout << "Достигнут максимальный размер массива NPC." << std::endl;
                    break;
                }
                npc->attach(consoleLogger);
                npc->attach(fileLogger);
                npcArray[npcCount++] = npc;
            }
            std::cout << "Загружено NPC из файла " << filename << std::endl;
        }
        else if (command.find("Выход") == 0) {
            break;
        }
        else {
            std::cout << "Неизвестная команда." << std::endl;
        }
    }

    return 0;
}

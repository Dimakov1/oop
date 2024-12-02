#include "NPCFactory.h"
#include "Dragon.h"
#include "Bull.h"
#include "Toad.h"
#include <fstream>
#include <sstream>

std::shared_ptr<NPC> NPCFactory::createNPC(const std::string& type, const std::string& name, int x, int y) {
    if (type == "Дракон") {
        return std::make_shared<Dragon>(name, x, y);
    }
    else if (type == "Бык") {
        return std::make_shared<Bull>(name, x, y);
    }
    else if (type == "Жаба") {
        return std::make_shared<Toad>(name, x, y);
    }
    else {
        return nullptr;
    }
}

std::vector<std::shared_ptr<NPC>> NPCFactory::loadFromFile(const std::string& filename) {
    std::vector<std::shared_ptr<NPC>> npcs;
    std::ifstream file(filename);
    if (!file.is_open()) return npcs;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type, name;
        int x, y;
        if (iss >> type >> name >> x >> y) {
            auto npc = createNPC(type, name, x, y);
            if (npc) {
                npcs.push_back(npc);
            }
        }
    }
    file.close();
    return npcs;
}

void NPCFactory::saveToFile(const std::string& filename, const std::vector<std::shared_ptr<NPC>>& npcs) {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            file << npc->getType() << " " << npc->getName() << " " << npc->getX() << " " << npc->getY() << std::endl;
        }
    }
    file.close();
}

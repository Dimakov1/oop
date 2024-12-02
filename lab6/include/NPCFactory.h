#ifndef NPCFACTORY_H
#define NPCFACTORY_H

#include <string>
#include <memory>
#include <vector>
#include "NPC.h"

class NPCFactory {
public:
    static std::shared_ptr<NPC> createNPC(const std::string& type, const std::string& name, int x, int y);
    static std::vector<std::shared_ptr<NPC>> loadFromFile(const std::string& filename);
    static void saveToFile(const std::string& filename, const std::vector<std::shared_ptr<NPC>>& npcs);
};

#endif 
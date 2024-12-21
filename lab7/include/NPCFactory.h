#ifndef NPCFACTORY_H
#define NPCFACTORY_H

#include <memory>
#include "NPC.h"

class NPCFactory {
public:
    static std::shared_ptr<NPC> createNPC(const std::string& type, int id, int x, int y);
    static std::shared_ptr<NPC> createRandomNPC(int id);
};

#endif 

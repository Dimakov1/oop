#ifndef TOAD_H
#define TOAD_H

#include "NPC.h"

class Toad : public NPC {
public:
    Toad(int id, int x, int y);

    std::string getType() const override;
    NPCStats getStats() const override;

    bool canAttack(const std::shared_ptr<NPC>& other) const override;
};

#endif 

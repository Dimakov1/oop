#ifndef DRAGON_H
#define DRAGON_H

#include "NPC.h"

class Dragon : public NPC {
public:
    Dragon(int id, int x, int y);

    std::string getType() const override;
    NPCStats getStats() const override;

    bool canAttack(const std::shared_ptr<NPC>& other) const override;
};

#endif 

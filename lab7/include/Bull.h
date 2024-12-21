#ifndef BULL_H
#define BULL_H

#include "NPC.h"

class Bull : public NPC {
public:
    Bull(int id, int x, int y);

    std::string getType() const override;
    NPCStats getStats() const override;

    bool canAttack(const std::shared_ptr<NPC>& other) const override;
};

#endif

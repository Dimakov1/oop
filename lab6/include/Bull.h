#ifndef BULL_H
#define BULL_H

#include "NPC.h"

class Bull : public NPC {
public:
    Bull(const std::string& name, int x, int y);

    void interactWith(NPC* other, Subject& logger) override;

    void attackedBy(Dragon* dragon, Subject& logger) override;
    void attackedBy(Bull* bull, Subject& logger) override;
    void attackedBy(Toad* toad, Subject& logger) override;

    std::string getType() const override;
};

#endif

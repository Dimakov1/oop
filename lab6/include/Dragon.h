#ifndef DRAGON_H
#define DRAGON_H

#include "NPC.h"

class Dragon : public NPC {
public:
    Dragon(const std::string& name, int x, int y);

    void interactWith(NPC* other, Subject& logger) override;

    void attackedBy(Dragon* dragon, Subject& logger) override;
    void attackedBy(Bull* bull, Subject& logger) override;
    void attackedBy(Toad* toad, Subject& logger) override;

    std::string getType() const override;
};

#endif 
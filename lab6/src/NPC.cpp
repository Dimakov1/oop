#include "NPC.h"

NPC::NPC(const std::string& name, int x, int y)
    : name(name), x(x), y(y), alive(true) {}

const std::string& NPC::getName() const {
    return name;
}

int NPC::getX() const {
    return x;
}

int NPC::getY() const {
    return y;
}

bool NPC::isAlive() const {
    return alive;
}

void NPC::setAlive(bool state) {
    alive = state;
}

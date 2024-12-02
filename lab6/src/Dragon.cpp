#include "Dragon.h"
#include "Bull.h"
#include "Toad.h"

Dragon::Dragon(const std::string& name, int x, int y)
    : NPC(name, x, y) {}

void Dragon::interactWith(NPC* other, Subject& logger) {
    if (!this->isAlive()) {
        return;
    }
    other->attackedBy(this, logger);
}

void Dragon::attackedBy(Dragon* dragon, Subject& logger) {
}

void Dragon::attackedBy(Bull* bull, Subject& logger) {
}

void Dragon::attackedBy(Toad* toad, Subject& logger) {
}

std::string Dragon::getType() const {
    return "Дракон";
}

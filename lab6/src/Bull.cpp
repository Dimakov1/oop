#include "Bull.h"
#include "Dragon.h"
#include "Toad.h"

Bull::Bull(const std::string& name, int x, int y)
    : NPC(name, x, y) {}

void Bull::interactWith(NPC* other, Subject& logger) {
    if (!this->isAlive()) {
        return;
    }
    other->attackedBy(this, logger);
}

void Bull::attackedBy(Dragon* dragon, Subject& logger) {
    if (!this->isAlive()) {
        return;
    }
    this->setAlive(false);
    std::string event = "Дракон " + dragon->getName() + " атаковал Быка " + this->getName() + ". Бык погиб.";
    logger.notify(event);
}

void Bull::attackedBy(Bull* bull, Subject& logger) {
}

void Bull::attackedBy(Toad* toad, Subject& logger) {
}

std::string Bull::getType() const {
    return "Бык";
}

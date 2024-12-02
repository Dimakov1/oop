#include "Toad.h"
#include "Dragon.h"
#include "Bull.h"

Toad::Toad(const std::string& name, int x, int y)
    : NPC(name, x, y) {}

void Toad::interactWith(NPC* other, Subject& logger) {
    if (!this->isAlive()) {
        return;
    }
}

void Toad::attackedBy(Dragon* dragon, Subject& logger) {
}

void Toad::attackedBy(Bull* bull, Subject& logger) {
    if (!this->isAlive()) {
        return;
    }
    this->setAlive(false);
    std::string event = "Бык " + bull->getName() + " затоптал Жабу " + this->getName() + ". Жаба погибла.";
    logger.notify(event);
}

void Toad::attackedBy(Toad* toad, Subject& logger) {
}

std::string Toad::getType() const {
    return "Жаба";
}

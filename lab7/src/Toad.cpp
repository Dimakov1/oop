#include "Toad.h"

Toad::Toad(int id, int x, int y)
    : NPC(id, x, y) {}

std::string Toad::getType() const {
    return "Toad";
}

NPCStats Toad::getStats() const {
    return {1, 10};
}

bool Toad::canAttack(const std::shared_ptr<NPC>& other) const {
    return false; 
}

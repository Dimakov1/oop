#include "Dragon.h"
#include "Bull.h"

Dragon::Dragon(int id, int x, int y)
    : NPC(id, x, y) {}

std::string Dragon::getType() const {
    return "Dragon";
}

NPCStats Dragon::getStats() const {
    return {50, 30};
}

bool Dragon::canAttack(const std::shared_ptr<NPC>& other) const {
    return other->getType() == "Bull";
}

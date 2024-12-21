#include "Bull.h"
#include "Toad.h"

Bull::Bull(int id, int x, int y)
    : NPC(id, x, y) {}

std::string Bull::getType() const {
    return "Bull";
}

NPCStats Bull::getStats() const {
    return {30, 10};
}

bool Bull::canAttack(const std::shared_ptr<NPC>& other) const {
    return other->getType() == "Toad";
}

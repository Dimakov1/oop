#include "NPCFactory.h"
#include "Dragon.h"
#include "Bull.h"
#include "Toad.h"
#include <random>

std::shared_ptr<NPC> NPCFactory::createNPC(const std::string& type, int id, int x, int y) {
    if (type == "Dragon") {
        return std::make_shared<Dragon>(id, x, y);
    } else if (type == "Bull") {
        return std::make_shared<Bull>(id, x, y);
    } else if (type == "Toad") {
        return std::make_shared<Toad>(id, x, y);
    }
    return nullptr;
}

std::shared_ptr<NPC> NPCFactory::createRandomNPC(int id) {
    static thread_local std::mt19937 rng(std::random_device{}()); 
    std::uniform_int_distribution<int> distType(0, 2);
    std::uniform_int_distribution<int> distX(0, MAP_WIDTH - 1);
    std::uniform_int_distribution<int> distY(0, MAP_HEIGHT - 1);

    int x = distX(rng);
    int y = distY(rng);
    int type = distType(rng);

    if (type == 0) {
        return std::make_shared<Dragon>(id, x, y);
    } else if (type == 1) {
        return std::make_shared<Bull>(id, x, y);
    } else {
        return std::make_shared<Toad>(id, x, y);
    }
}

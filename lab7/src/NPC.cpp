#include "NPC.h"
#include <algorithm>

const int MAP_WIDTH = 20;  
const int MAP_HEIGHT = 20;

NPC::NPC(int id, int x, int y)
    : id(id), x(x), y(y), alive(true) {}

int NPC::getX() const {
    return x;
}

int NPC::getY() const {
    return y;
}

void NPC::setPosition(int newX, int newY) {
    x = std::clamp(newX, 0, MAP_WIDTH - 1);
    y = std::clamp(newY, 0, MAP_HEIGHT - 1);
}

int NPC::getId() const {
    return id;
}

bool NPC::isAlive() const {
    return alive;
}

void NPC::setAlive(bool state) {
    alive = state;
}

std::shared_mutex& NPC::getMutex() {
    return npcMutex;
}

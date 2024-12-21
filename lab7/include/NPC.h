#ifndef NPC_H
#define NPC_H

#include <string>
#include <shared_mutex>

extern const int MAP_WIDTH;
extern const int MAP_HEIGHT;

struct NPCStats {
    int moveDistance;
    int killDistance;
};

class NPC {
public:
    NPC(int id, int x, int y);
    virtual ~NPC() = default;

    virtual std::string getType() const = 0;
    virtual NPCStats getStats() const = 0;

    int getX() const;
    int getY() const;
    void setPosition(int newX, int newY);

    int getId() const;

    bool isAlive() const;
    void setAlive(bool state);

    std::shared_mutex& getMutex();

    virtual bool canAttack(const std::shared_ptr<NPC>& other) const = 0;

protected:
    int id;
    int x, y;
    bool alive;
    std::shared_mutex npcMutex;
};

#endif 

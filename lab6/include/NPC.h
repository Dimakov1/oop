#ifndef NPC_H
#define NPC_H

#include <string>
#include "Subject.h"

class Dragon;
class Bull;
class Toad;

class NPC : public Subject {
public:
    NPC(const std::string& name, int x, int y);
    virtual ~NPC() = default;

    virtual void interactWith(NPC* other, Subject& logger) = 0;

    virtual void attackedBy(Dragon* dragon, Subject& logger) = 0;
    virtual void attackedBy(Bull* bull, Subject& logger) = 0;
    virtual void attackedBy(Toad* toad, Subject& logger) = 0;

    const std::string& getName() const;
    int getX() const;
    int getY() const;
    bool isAlive() const;
    void setAlive(bool state);

    virtual std::string getType() const = 0;

protected:
    std::string name;
    int x, y;
    bool alive;
};

#endif 

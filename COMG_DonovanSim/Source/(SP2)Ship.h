#ifndef SHIP_H
#define SHIP_H

#include "(SP2)GameObject.h"
#include <Queue>

using std::queue;

class Ship : public GameObject
{
public:
    Ship(string name, Position pos);
    ~Ship();

    float shipSpeed;
    float maxSpeed;
};

#endif
#ifndef SHIP_H
#define SHIP_H

#include "(SP2)InteractableOBJs.h"
#include <Queue>

using std::queue;

class Ship : public InteractableOBJs
{
public:
    Ship(string name, Position maxPos, Position minPos, Position offSet, int scaleOffSet, float rotateAngle, Vector3 rotateAxis);
    ~Ship();

    float shipSpeed;
    float maxSpeed;

};

#endif
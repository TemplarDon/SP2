#ifndef BUILDING_H
#define BUILDING_H

#include "(SP2)CollisionOBJs.h"

class Building : public CollisionOBJs
{
private:

public:
    Building(string name, Position maxPos, Position minPos, Position offSet, int scaleOffSet, float rotateAngle, Vector3 rotateAxis);
    ~Building();

};

#endif
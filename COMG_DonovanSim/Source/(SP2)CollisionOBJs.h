#ifndef COLLISION_OBJ_H
#define COLLISION_OBJ_H

#include "(SP2)GameObject.h"

class CollisionOBJs : public GameObject
{
protected:
    Position maxPos;
    Position minPos;

    Position offSet;
    int scaleOffSet;

    float rotateAngle;
    Vector3 rotateAxis;

    string name;
public:
    bool canMove;

    CollisionOBJs(string name, Position maxPos, Position minPos, Position offSet, int scaleOffSet, float rotateAngle, Vector3 rotateAxis);
    ~CollisionOBJs() = 0;
};

#endif
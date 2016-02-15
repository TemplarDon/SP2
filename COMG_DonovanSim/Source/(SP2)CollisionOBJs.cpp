#include "(SP2)CollisionOBJs.h"

CollisionOBJs::CollisionOBJs(string name, Position maxPos, Position minPos, Position offSet, int scaleOffSet, float rotateAngle, Vector3 rotateAxis) : GameObject(name)
{
    this->maxPos = maxPos;
    this->minPos = minPos;
    this->offSet = offSet;
    this->scaleOffSet = scaleOffSet;

    this->rotateAngle = rotateAngle;
    this->rotateAxis = rotateAxis;
}

CollisionOBJs::~CollisionOBJs()
{

}
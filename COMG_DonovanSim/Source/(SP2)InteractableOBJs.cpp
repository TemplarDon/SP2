#include "(SP2)InteractableOBJs.h"

InteractableOBJs::InteractableOBJs(string name, Position maxPos, Position minPos, Position offSet, int scaleOffSet, float rotateAngle, Vector3 rotateAxis) : CollisionOBJs(name, maxPos, minPos, offSet, scaleOffSet, rotateAngle, rotateAxis), pos(offSet)
{

}

InteractableOBJs::~InteractableOBJs()
{

}
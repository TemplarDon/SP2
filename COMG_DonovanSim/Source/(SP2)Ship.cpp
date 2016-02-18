#include "(SP2)Ship.h"

Ship::Ship(string name, Position maxPos, Position minPos, Position offSet, int scaleOffSet, float rotateAngle, Vector3 rotateAxis) : InteractableOBJs(name, maxPos, minPos, offSet, scaleOffSet, rotateAngle, rotateAxis)
{

}

Ship::~Ship()
{

}
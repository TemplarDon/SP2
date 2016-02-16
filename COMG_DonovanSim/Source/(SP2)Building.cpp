#include "(SP2)Building.h"

Building::Building(string name, Position maxPos, Position minPos, Position offSet, int scaleOffSet, float rotateAngle, Vector3 rotateAxis) : CollisionOBJs(name, maxPos, minPos, offSet, scaleOffSet, rotateAngle, rotateAxis)
{

}

Building::~Building()
{

}
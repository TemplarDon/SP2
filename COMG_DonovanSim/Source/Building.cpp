/*************************************************************************************************/
/*!
\file   Building.cpp
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Contains code for initialising Building
*/
/*************************************************************************************************/
#include "Building.h"

/******************************************************************************/
/*!
\brief
    Building Constructor

\param  name
    name of Building (Eg. Wall 1)
\param maxPos
    maximum position of the building (used to create a collision box for collision detection)
\param minPos                          
    minimum position of the building (used to create a collision box for collision detection)
\param offSet
    offSet for moving the min and max positions, thus moving the collision box as well
\param scaleOffSet
    scaleOffSet for scaling up the collision box in order to match with the Building if it is scaled in Render()
\param rotateAngle
    angle to rotate collision box by (not working)
\param rotateAxis
    axis to rotate collision box by (not working)
*/
/******************************************************************************/
Building::Building(string name, Position maxPos, Position minPos, Position offSet, int scaleOffSet, float rotateAngle, Vector3 rotateAxis) : CollisionOBJs(name, maxPos, minPos, offSet, scaleOffSet, rotateAngle, rotateAxis)
{
    this->gateOffset = 0;
}

/******************************************************************************/
/*!
\brief
    Building Destructor
*/
/******************************************************************************/
Building::~Building()
{

}
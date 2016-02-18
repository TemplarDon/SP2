/*************************************************************************************************/
/*!
\file   CollisionOBJs.cpp
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Contains code for CollisionOBJs class
*/
/*************************************************************************************************/
#include "(SP2)CollisionOBJs.h"

/******************************************************************************/
/*!
\brief
CollisionOBJs Constructor

\param  name
    name of CollisionOBJ (Eg. Wall 1)
\param maxPos
    maximum position of the CollisionOBJ (used to create a collision box for collision detection)
\param minPos
    minimum position of the CollisionOBJ (used to create a collision box for collision detection)
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
CollisionOBJs::CollisionOBJs(string name, Position maxPos, Position minPos, Position offSet, int scaleOffSet, float rotateAngle, Vector3 rotateAxis) : GameObject(name, offSet)
{
    this->maxPos = maxPos;
    this->minPos = minPos;
    //this->offSet = offSet;
    this->scaleOffSet = scaleOffSet;

    this->rotateAngle = rotateAngle;
    this->rotateAxis = rotateAxis;
}

/******************************************************************************/
/*!
\brief
    CollisionOBJs Destructor
*/
/******************************************************************************/
CollisionOBJs::~CollisionOBJs()
{

}
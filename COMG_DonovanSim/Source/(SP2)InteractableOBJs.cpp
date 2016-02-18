/*************************************************************************************************/
/*!
\file   InteractableOBJs.cpp
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Contains code for InteractableOBJs class
*/
/*************************************************************************************************/
#include "(SP2)InteractableOBJs.h"

/******************************************************************************/
/*!
\brief
InteractableOBJs Constructor

\param  name
    name of InteractableOBJs (Eg. Wall 1)
\param maxPos
    maximum position of the InteractableOBJs (used to create a collision box for collision detection)
\param minPos
    minimum position of the InteractableOBJs (used to create a collision box for collision detection)
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
InteractableOBJs::InteractableOBJs(string name, Position maxPos, Position minPos, Position offSet, int scaleOffSet, float rotateAngle, Vector3 rotateAxis) : CollisionOBJs(name, maxPos, minPos, offSet, scaleOffSet, rotateAngle, rotateAxis)
{
    this->effectOver = false;
}

/******************************************************************************/
/*!
\brief
    InteractableOBJs Destructor
*/
/******************************************************************************/
InteractableOBJs::~InteractableOBJs()
{

}
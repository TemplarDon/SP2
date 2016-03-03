/*************************************************************************************************/
/*!
\file   InteractableOBJs.cpp
\brief
    Contains code for InteractableOBJs class
*/
/*************************************************************************************************/
#include "InteractableOBJs.h"

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
InteractableOBJs::InteractableOBJs(string name, Position maxPos, Position minPos, Position offSet, float scaleOffSet, float rotateAngle, Vector3 rotateAxis)
: CollisionOBJs(name, maxPos, minPos, offSet, scaleOffSet, rotateAngle, rotateAxis)
{
    this->effectOver = false;
    requiredDistanceSquared = 100;
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

/******************************************************************************/
/*!
\brief
    Function to check if object is in view of player
\param  charPos
    position of player / point from which the function checks
\param  maxPos
    view vector
\returns
    returns a bool, if true, object is in view
*/
/******************************************************************************/
bool InteractableOBJs::isInView(const Position &charPos, const Vector3 &viewDirection) 
{
	Vector3 P1 = Vector3(charPos.x, charPos.y, charPos.z);
	Vector3 P2 = Vector3(pos.x, pos.y, pos.z);

	Vector3 D = P2 - P1;
	Vector3 V = viewDirection.Normalized();

	//std::cout << (D - D.Dot(V)*V).LengthSquared() << std::endl;
	//Check if within distance
	if (D.LengthSquared() > requiredDistanceSquared) return false;

	//Check if focusing on point
	//std::cout << "Is near" << std::endl;
	if (D.Dot(V) < 0) return false;
	return (D - D.Dot(V)*V).LengthSquared() < requiredFocusSquared;
	
}

/******************************************************************************/
/*!
\brief
    Function to set the distance and focus required for isInView() function
\param  distance
    distance / range for isInView() function 
\param  focus
    focus for isInView() function
*/
/******************************************************************************/
void InteractableOBJs::setRequirements(const float distance, const float focus)
{
	requiredFocusSquared = focus * focus;
	requiredDistanceSquared = distance* distance;
}

/******************************************************************************/
/*!
\brief
    Function to get the focus required for isInView() function
\return
    Returns a float, the required focus
*/
/******************************************************************************/
float InteractableOBJs::getRequiredFocus()
{
	return sqrt(requiredFocusSquared);
}

/******************************************************************************/
/*!
\brief
    Sets the object's bool 
\param  someBool
    The bool to be set to (true/false)
*/
/******************************************************************************/
void InteractableOBJs::setEffectOverBool(bool someBool)
{
    this->effectOver = someBool;
}


/******************************************************************************/
/*!
\brief
    Gets the object's bool (true/false)
\return  
    Returns the bool of the object
*/
/******************************************************************************/
bool InteractableOBJs::getEffectOverBool()
{
    return this->effectOver;
}
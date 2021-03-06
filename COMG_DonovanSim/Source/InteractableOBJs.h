/*************************************************************************************************/
/*!
\file   InteractableOBJs.h
\brief
    Header File for the InteractableOBJs Class with parent class CollisionOBJs, used for collision detection with objects that require collisions and interactions
*/
/*************************************************************************************************/
#ifndef INTERACTABLE_OBJ_H
#define INTERACTABLE_OBJ_H

#include "CollisionOBJs.h"

/*************************************************************************************************/
/*!
Class InteractableOBJs : public CollisionOBJs
\brief
    Class InteractableOBJs, with parent class CollisionOBJs. Contains Constructor/ Destructor for InteractableOBJs
*/
/*************************************************************************************************/
class InteractableOBJs : public CollisionOBJs
{
private:
    // Bool to check if interaction for object is over
    /******************************************************************************/
    /*!
    \brief
        Bool to check if interaction for object is over
    */
    /******************************************************************************/
    bool effectOver;

    /******************************************************************************/
    /*!
    \brief
        Squared value of focus
    */
    /******************************************************************************/
	float requiredFocusSquared;

    /******************************************************************************/
    /*!
    \brief
        Squared value of distance
    */
    /******************************************************************************/
	float requiredDistanceSquared;

public:
    InteractableOBJs(string name, Position maxPos, Position minPos, Position offSet, float scaleOffSet, float rotateAngle, Vector3 rotateAxis);
    ~InteractableOBJs();

    void setEffectOverBool(bool newBool);
    bool getEffectOverBool();

	void setRequirements(const float distance, const float focus);
	float getRequiredFocus();

	bool isInView(const Position &pos, const Vector3 &viewDirection);
};

#endif
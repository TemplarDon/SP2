/*************************************************************************************************/
/*!
\file   CollisionOBJs.h
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Header File for the CollisionOBJs Abstract Base Class, used for collision detection with objects that require collisions
*/
/*************************************************************************************************/
#ifndef COLLISION_OBJ_H
#define COLLISION_OBJ_H

#include "GameObject.h"

/*************************************************************************************************/
/*!
Class CollisionOBJs : public GameObject
\brief
    Class CollisionOBJs, with parent class GameObject. Contains Constructor/ Destructor for CollisionOBJs
*/
/*************************************************************************************************/
class CollisionOBJs : public GameObject
{
protected:

    CollisionOBJs(string name, Position maxPos, Position minPos, Position offSet, float scaleOffSet, float rotateAngle, Vector3 rotateAxis);

public:
    // Bool to check if player can move thru this object
    /******************************************************************************/
    /*!
    \brief
        Bool to check if player can't move or not
    */
    /******************************************************************************/
    bool canMove;
    ~CollisionOBJs() = 0;

    // Max Position of this object, used to create a collision box
    /******************************************************************************/
    /*!
    \brief
        Max Position of this object, used to create a collision box
    */
    /******************************************************************************/
    Position maxPos;

    // Min Position of this object, used to create a collision box
    /******************************************************************************/
    /*!
    \brief
        Min Position of this object, used to create a collision box
    */
    /******************************************************************************/
    Position minPos;

    /******************************************************************************/
    /*!
    \brief
        Offset to scale collision box by
    */
    /******************************************************************************/
    float scaleOffSet;

    // Rotate Angle, used to rotate collision box
    float rotateAngle;

    // Axis to rotate collision box by
    Vector3 rotateAxis;

};

#endif
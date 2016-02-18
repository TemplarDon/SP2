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

#include "(SP2)GameObject.h"

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


    CollisionOBJs(string name, Position maxPos, Position minPos, Position offSet, int scaleOffSet, float rotateAngle, Vector3 rotateAxis);

public:
    // Bool to check if player can move thru this object
    bool canMove;
    ~CollisionOBJs() = 0;

    // Max Position of this object, used to create a collision box
    Position maxPos;

    // Min Position of this object, used to create a collision box
    Position minPos;

    // Position offSet;
    int scaleOffSet;

    // Rotate Angle, used to rotate collision box
    float rotateAngle;

    // Axis to rotate collision box by
    Vector3 rotateAxis;

};

#endif
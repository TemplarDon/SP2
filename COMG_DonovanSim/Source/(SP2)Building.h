/*************************************************************************************************/
/*!
\file   Building.h
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Header File for the Building Class, used for collision detection with objects that do not require an interaction
*/
/*************************************************************************************************/
#ifndef BUILDING_H
#define BUILDING_H

#include "(SP2)CollisionOBJs.h"

/*************************************************************************************************/
/*!
Class Building : public CollisionOBJs
\brief  
    Class Building, with parent class CollisionOBJs. Contains Constructor/ Destructor for Building
*/
/*************************************************************************************************/
class Building : public CollisionOBJs
{
private:

public:
    Building(string name, Position maxPos, Position minPos, Position offSet, int scaleOffSet, float rotateAngle, Vector3 rotateAxis);
    ~Building();

};

#endif
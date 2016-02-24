/*************************************************************************************************/
/*!
\file   Wings.h
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Header File for the Wings Class, with parent class ShipParts
*/
/*************************************************************************************************/
#ifndef WINGS_H
#define WINGS_H

#include "ShipParts.h"

/*************************************************************************************************/
/*!
Class Ship : public ShipParts
\brief
    Class Ship, with parent class ShipParts. Contains Constructor/ Destructor for Ship
*/
/*************************************************************************************************/
class Wings : public ShipParts
{
public:
    Wings(string name);
    ~Wings();

private:
};

#endif
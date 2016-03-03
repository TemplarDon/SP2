/*************************************************************************************************/
/*!
\file   ShipBuilder.h
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Header File for the ShipBuilder Class
*/
/*************************************************************************************************/
#ifndef SHIP_BUILDER_H
#define SHIP_BUILDER_H

#include "Ship.h"

/*************************************************************************************************/
/*!
Class ShipBuilder
\brief
    Class ShipBuilder. Contains Constructor/ Destructor for ShipBuilder and createShip function
*/
/*************************************************************************************************/
class ShipBuilder
{
public:
    ShipBuilder();
    ~ShipBuilder();

    // Function to create a ship 
    Ship createShip(Ship* templateShip, list<ShipParts*> partsList);
};

#endif
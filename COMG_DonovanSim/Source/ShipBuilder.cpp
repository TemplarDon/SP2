/*************************************************************************************************/
/*!
\file   ShipBuilder.cpp
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Contains code for ShipBuilder class and functions
*/
/*************************************************************************************************/
#include "ShipBuilder.h"

/******************************************************************************/
/*!
\brief
    ShipBuilder Constructor
*/
/******************************************************************************/
ShipBuilder::ShipBuilder()
{}

/******************************************************************************/
/*!
\brief
    ShipBuilder Destrucctor
*/
/******************************************************************************/
ShipBuilder::~ShipBuilder()
{}

/******************************************************************************/
/*!
\brief
    Function to create a ship
\param  name
    name of ship to be created
\param  pos
    position of the ship to be made
\param  partsList
    list of parts to be added
\returns
    returns a ship

*/
/******************************************************************************/
Ship ShipBuilder::createShip(Ship* templateShip, list<ShipParts*>partsList)
{
    for (list<ShipParts*>::iterator it = partsList.begin(); it != partsList.end(); ++it)
    {
        templateShip->addShipPart(*it);
    }
    templateShip->calculateShipStats();

    return *templateShip;
}
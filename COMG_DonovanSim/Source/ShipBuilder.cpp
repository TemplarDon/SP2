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
\param  HullPart
    object of class Hull, used to make the ship
\param  WingsPart
    object of class Wings, used to make the ship
\param  EngineParts
    object of class Engine, used to make the ship
\param  upgradesVec
    vector containing the ship's upgrades
\returns
    returns a ship
    
*/
/******************************************************************************/
Ship ShipBuilder::createShip(Ship* templateShip, Hull HullPart, Wings WingsPart, Engine EnginePart)
{
    templateShip->addShipPart(HullPart);
    templateShip->addShipPart(WingsPart);
    templateShip->addShipPart(EnginePart);
    templateShip->calculateShipStats();

    return *templateShip;
}


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
Ship ShipBuilder::createShip(Ship* templateShip, list<ShipParts>partsList)
{
    for (list<ShipParts>::iterator it = partsList.begin(); it != partsList.end(); ++it)
    {
        templateShip->addShipPart(*it);
    }
    templateShip->calculateShipStats();

    return *templateShip;
}
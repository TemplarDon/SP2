/*************************************************************************************************/
/*!
\file   ShipBuilder.cpp
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Contains code for ShipBuilder class and functions
*/
/*************************************************************************************************/
#include "(SP2)ShipBuilder.h"

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
\param
    object of class Wings, used to make the ship
\param
    object of class Engine, used to make the ship
\param  upgradesVec
    vector containing the ship's upgrades
    
*/
/******************************************************************************/
Ship* ShipBuilder::createShip(string name, Position pos, Hull HullPart, Wings WingsPart, Engine EnginePart, vector<Ship_Upgrade>upgradesVec)
{
    //Ship * someShip = new Ship(name, maxPos, minPos, offSet, scaleOffSet, rotateAngle, rotateAxis);
    //someShip->addShipPart(HullPart);
    //someShip->addShipPart(WingsPart);
    //someShip->addShipPart(EnginePart);

    //return someShip;

    return 0;
}

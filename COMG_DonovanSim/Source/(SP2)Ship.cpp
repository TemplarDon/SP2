/*************************************************************************************************/
/*!
\file   Ship.cpp
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Contains code for Ship class and functions
*/
/*************************************************************************************************/
#include "(SP2)Ship.h"

/******************************************************************************/
/*!
\brief
    Ship Constructor
\param name
    Ship's name
\param pos
    Ship's pos
*/
/******************************************************************************/
Ship::Ship(string name, Position pos) : GameObject(name, pos)
{

}

/******************************************************************************/
/*!
\brief
Player Destructor
*/
/******************************************************************************/
Ship::~Ship()
{

}

/******************************************************************************/
/*!
\brief
    Function to add parts to the ship
\param  somePart
    part to be added into the ship
*/
/******************************************************************************/
void Ship::addShipPart(ShipParts &somePart)
{
    this->ShipPartsVector.push_back(somePart);
}

/******************************************************************************/
/*!
\brief
    Function to add upgrades to the ship
\param  someupgrade
    upgrade to be added into the ship
*/
/******************************************************************************/
void Ship::addShipUpgrade(Ship_Upgrade &someUpgrade)
{
    this->addShipUpgrade(someUpgrade);
}

/******************************************************************************/
/*!
\brief
    Function to calculate the ship's stats using its parts and upgrades
*/
/******************************************************************************/
void Ship::calculateShipStats()
{
    string wings = "Wings";
    string engine = "Engine";
    for (vector<ShipParts>::iterator it = ShipPartsVector.begin(); it != ShipPartsVector.end(); ++it)
    {
        if (it->getName().find(wings) != string::npos)
        {
            this->shipSpeed += it->partsEffect();
        }
        else if (it->getName().find(engine) != string::npos)
        {
            this->maxSpeed += it->partsEffect();
        }

    }
}
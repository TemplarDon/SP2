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
\param  name
    name of Ship (Eg. Wall 1)
\param maxPos
    maximum position of the Ship (used to create a collision box for collision detection)
\param minPos
    minimum position of the Ship (used to create a collision box for collision detection)
\param offSet
    offSet for moving the min and max positions, thus moving the collision box as well
\param scaleOffSet
    scaleOffSet for scaling up the collision box in order to match with the Building if it is scaled in Render()
\param rotateAngle
    angle to rotate collision box by (not working)
\param rotateAxis
    axis to rotate collision box by (not working)
*/
/******************************************************************************/
Ship::Ship(string name, Position maxPos, Position minPos, Position offSet, int scaleOffSet, float rotateAngle, Vector3 rotateAxis) : InteractableOBJs(name, maxPos, minPos, offSet, scaleOffSet, rotateAngle, rotateAxis)
{
    shipSpeed = 0;
    turningSpeed = 0;
}

/******************************************************************************/
/*!
\brief
    Ship Destructor
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
    string hull = "Hull";
    for (vector<ShipParts>::iterator it = ShipPartsVector.begin(); it != ShipPartsVector.end(); ++it)
    {
        if (it->getName().find(wings) != string::npos)
        {
            this->turningSpeed += it->partsEffect();
            this->wingType = it->getName();
        }
        if (it->getName().find(engine) != string::npos)
        {
            this->shipSpeed += it->partsEffect();
            this->engineType = it->getName();
        }
        if (it->getName().find(hull) != string::npos)
        {
            this->hullType = it->getName();
        }

    }
}
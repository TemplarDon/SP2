/*************************************************************************************************/
/*!
\file   Ship.cpp
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Contains code for Ship class and functions
*/
/*************************************************************************************************/
#include "Ship.h"

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
Ship::Ship(string name, Position maxPos, Position minPos, Position offSet, float scaleOffSet, float rotateAngle, Vector3 rotateAxis, Vector3 target) : InteractableOBJs(name, maxPos, minPos, offSet, scaleOffSet, rotateAngle, rotateAxis)
{
    shipSpeed = 0;
    shipMaxSpeed = 0;
    shipSpeedGain = 0;
    turningSpeed = 0;
    shipLandingSpeed = 2;
    shipTakeoff = false;
    Vector3 position = { pos.x, pos.y, pos.z };
    this->defaultShipDirection = shipDirection = (target - position).Normalized();
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
void Ship::addShipPart(ShipParts* somePart)
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

    this->ShipUpgradeVector.push_back(someUpgrade);
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

    for (size_t i = 0; i < ShipPartsVector.size(); ++i)
    {
        if (ShipPartsVector[i]->getName().find(wings) != string::npos)
        {
            this->turningSpeed = ShipPartsVector[i]->partsEffect();
            this->wingType = ShipPartsVector[i]->getName();
        }
        if (ShipPartsVector[i]->getName().find(engine) != string::npos)
        {
            this->shipSpeedGain = ShipPartsVector[i]->partsEffect();
            this->engineType = ShipPartsVector[i]->getName();
        }
        if (ShipPartsVector[i]->getName().find(hull) != string::npos)
        {
            this->shipMaxSpeed = ShipPartsVector[i]->partsEffect();
            this->hullType = ShipPartsVector[i]->getName();
        }
    }
}

/******************************************************************************/
/*!
\brief
    Function to set ship's direction
*/
/******************************************************************************/
void Ship::setDirectionalVectors(Vector3 direction, Vector3 right)
{
    this->shipDirection = direction;
    this->shipRightVec = right;
}

/******************************************************************************/
/*!
\brief
    Overloaded Function to set ship's direction only
*/
/******************************************************************************/
void Ship::setDirectionalVectors(Vector3 direction)
{
    this->shipDirection = direction;
}
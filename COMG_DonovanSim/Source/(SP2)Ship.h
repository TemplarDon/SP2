/*************************************************************************************************/
/*!
\file   Ship.h
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Header File for the Ship Class, contains ship stats
*/
/*************************************************************************************************/
#ifndef SHIP_H
#define SHIP_H

#include "(SP2)InteractableOBJs.h"
#include "(SP2)AllParts.h"
#include "(SP2)AllUpgrades.h"

/*************************************************************************************************/
/*!
Class Ship : public CollisionOBJs
\brief
    Class Ship. Contains Constructor/ Destructor for Ship and ship stats
*/
/*************************************************************************************************/
class Ship : public InteractableOBJs
{
public:
    Ship(string name, Position maxPos, Position minPos, Position offSet, int scaleOffSet, float rotateAngle, Vector3 rotateAxis);
    ~Ship();

    // Ship's Speed
    float shipSpeed;

    // Ship's Max Speed
    float maxSpeed;

    // Vector Containing the Ships's Parts
    vector<ShipParts> ShipPartsVector;

    // Vector Containing the Ship's Upgrades
    vector<Ship_Upgrade> ShipUpgradeVector;

    // Function to add a part to the ship
    void addShipPart(ShipParts &somePart);

    // Function to add a upgrade to the ship
    void addShipUpgrade(Ship_Upgrade &someUpgrade);

    // Function to calculate the ship's stats using its parts and upgrades
    void calculateShipStats();
};

#endif
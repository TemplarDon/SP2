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

#include "InteractableOBJs.h"
#include "AllParts.h"
#include "AllUpgrades.h"

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

    // Const rate which speed is gained
    float shipSpeedGain;

    // Ship Direction
    Vector3 shipDirection;
    Vector3 shipRightVec;

    // Speed needed to land
    float shipLandingSpeed;

    // Ship's Max Speed
    float shipMaxSpeed;

    // Ship's Turning Speed
    float turningSpeed;

    // Vector Containing the Ships's Parts
    vector<ShipParts*> ShipPartsVector;

    // Vector Containing the Ship's Upgrades
    vector<Ship_Upgrade> ShipUpgradeVector;

    // Function to add a part to the ship
    void addShipPart(ShipParts* somePart);

    // Function to add a upgrade to the ship
    void addShipUpgrade(Ship_Upgrade &someUpgrade);

    // Function to calculate the ship's stats using its parts and upgrades
    void calculateShipStats();

    // Function to set Ship's Directional Vectors
    void setDirectionalVectors(Vector3 direction, Vector3 right);
    void setDirectionalVectors(Vector3 direction);

    string hullType;
    string wingType;
    string engineType;

    bool shipTakeoff;
};

#endif
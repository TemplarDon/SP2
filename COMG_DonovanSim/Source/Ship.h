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
    Ship(string name, Position maxPos, Position minPos, Position offSet, float scaleOffSet, float rotateAngle, Vector3 rotateAxis, Vector3 target);
    ~Ship();


    // Ship's Speed
    /******************************************************************************/
    /*!
    \brief
        Ship's Speed
    */
    /******************************************************************************/
    float shipSpeed;

    // Const rate which speed is gained
    /******************************************************************************/
    /*!
    \brief
        Ship's speed gain
    */
    /******************************************************************************/
    float shipSpeedGain;

    // Ship Direction
    /******************************************************************************/
    /*!
    \brief
        Ship's Direction vector
    */
    /******************************************************************************/
    Vector3 shipDirection;

    /******************************************************************************/
    /*!
    \brief
        Ship's right vector
    */
    /******************************************************************************/
    Vector3 shipRightVec;

    /******************************************************************************/
    /*!
    \brief
        default ship's direction
    */
    /******************************************************************************/
    Vector3 defaultShipDirection;

    // Speed needed to land
    /******************************************************************************/
    /*!
    \brief
        Speed required in order to land
    */
    /******************************************************************************/
    float shipLandingSpeed;

    // Ship's Max Speed
    /******************************************************************************/
    /*!
    \brief
        Ship's maximum speed
    */
    /******************************************************************************/
    float shipMaxSpeed;

    // Ship's Turning Speed
    /******************************************************************************/
    /*!
    \brief
        Ship's turning speed
    */
    /******************************************************************************/
    float turningSpeed;

    // Vector Containing the Ships's Parts
    /******************************************************************************/
    /*!
    \brief
        Vector of Ship's Parts
    */
    /******************************************************************************/
    vector<ShipParts*> ShipPartsVector;

    // Vector Containing the Ship's Upgrades
    /******************************************************************************/
    /*!
    \brief
        Vector of Ship's Upgrade
    */
    /******************************************************************************/
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

    /******************************************************************************/
    /*!
    \brief
        string of Hull Type
    */
    /******************************************************************************/
    string hullType;

    /******************************************************************************/
    /*!
    \brief
        string of Wing Type
    */
    /******************************************************************************/
    string wingType;

    /******************************************************************************/
    /*!
    \brief
        string of Engine Type
    */
    /******************************************************************************/
    string engineType;

    /******************************************************************************/
    /*!
    \brief
        bool to check if ship has taken off
    */
    /******************************************************************************/
    bool shipTakeoff;
};

#endif
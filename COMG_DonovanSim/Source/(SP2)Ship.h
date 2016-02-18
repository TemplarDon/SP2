#ifndef SHIP_H
#define SHIP_H

#include "(SP2)GameObject.h"
#include "(SP2)AllParts.h"
#include "(SP2)AllUpgrades.h"

class Ship : public GameObject
{
public:
    Ship(string name, Position pos);
    ~Ship();

    float shipSpeed;
    float maxSpeed;
    vector<ShipParts> ShipPartsVector;
    vector<Ship_Upgrade> ShipUpgradeVector;

    void addShipPart(ShipParts &somePart);
    void addShipUpgrade(Ship_Upgrade &someUpgrade);

    void calculateShipStats();
};

#endif
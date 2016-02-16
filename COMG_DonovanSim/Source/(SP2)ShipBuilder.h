#ifndef SHIP_BUILDER_H
#define SHIP_BUILDER_H

#include "(SP2)Ship.h"
#include "(SP2)AllParts.h"
#include "(SP2)AllUpgrades.h"

class ShipBuilder
{
public:
    ShipBuilder();
    ~ShipBuilder();

    //Ship* createShip(string name, Position pos, Light_Hull Hull, Dual_Wings Wings, G1_Engine Engine, vector<Ship_Upgrade>upgradesVec);
    //Ship* createShip(string name, Position pos, ShipParts Hull, ShipParts Wings, ShipParts Engine, vector<Ship_Upgrade>upgradesVec);
};

#endif
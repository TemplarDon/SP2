#ifndef SHIP_BUILDER_H
#define SHIP_BUILDER_H

#include "(SP2)Ship.h"

class ShipBuilder
{
public:
    ShipBuilder();
    ~ShipBuilder();

    Ship* createShip(string name, Position pos, Hull Hull, Wings Wings, Engine Engine, vector<Ship_Upgrade>upgradesVec);
};

#endif
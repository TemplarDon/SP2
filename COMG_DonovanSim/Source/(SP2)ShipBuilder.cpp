#include "(SP2)ShipBuilder.h"

ShipBuilder::ShipBuilder()
{}

ShipBuilder::~ShipBuilder()
{}

Ship* ShipBuilder::createShip(string name, Position pos, Hull HullPart, Wings WingsPart, Engine EnginePart, vector<Ship_Upgrade>upgradesVec)
{
    Ship * someShip = new Ship(name, pos);
    someShip->addShipPart(HullPart);
    someShip->addShipPart(WingsPart);
    someShip->addShipPart(EnginePart);

    return someShip;
}

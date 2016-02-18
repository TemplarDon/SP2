#include "(SP2)Ship.h"

Ship::Ship(string name, Position pos) : GameObject(name, pos)
{

}

Ship::~Ship()
{

}

void Ship::addShipPart(ShipParts &somePart)
{
    this->ShipPartsVector.push_back(somePart);
}

void Ship::addShipUpgrade(Ship_Upgrade &someUpgrade)
{
    this->addShipUpgrade(someUpgrade);
}

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
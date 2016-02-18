#include "(SP2)ShipParts.h"

ShipParts::ShipParts(string name) : name(name)
{
}

ShipParts::~ShipParts()
{
}

string ShipParts::getName()
{
    return this->name;
}

int ShipParts::partsEffect()
{
    return 0;
}
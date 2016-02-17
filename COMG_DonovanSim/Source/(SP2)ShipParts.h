#ifndef SHIP_PARTS_H
#define SHIP_PARTS_H

#include <string>
using std::string;

class ShipParts
{
protected:
    ShipParts(string name);

    string name;
    virtual void partsEffect();
public:
    virtual ~ShipParts() = 0;

};


#endif
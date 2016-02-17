#ifndef SHIP_UPGRADE_H
#define SHIP_UPGARDE_H

#include <string>
using std::string;

class Ship_Upgrade
{
protected:
    Ship_Upgrade(string name);

    string name;
    virtual void useUpgradeEffect();
public:
    virtual ~Ship_Upgrade() = 0;

};

#endif
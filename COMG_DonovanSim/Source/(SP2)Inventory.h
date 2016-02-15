#ifndef INVENTORY_H
#define INVENTORY_H
#include "(SP2)GameObject.h"

class Inventory
{
public:
    Inventory();
    ~Inventory();

    int moneyAmount;
    list<string> itemList;
private:

};

#endif
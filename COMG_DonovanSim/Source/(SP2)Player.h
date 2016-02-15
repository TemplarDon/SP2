#ifndef PLAYER_H
#define PLAYER_H

#include "(SP2)GameObject.h"
#include "(SP2)Inventory.h"

class Player : public GameObject
{
public:
    Player(string name, string race);
    ~Player();

    void addItem(string itemName);
    void removeItem(string itemName);
    
private:
    string race;
    Inventory playerInventory;

};

#endif
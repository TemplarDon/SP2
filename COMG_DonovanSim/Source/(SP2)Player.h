#ifndef PLAYER_H
#define PLAYER_H

#include "(SP2)GameObject.h"
#include "(SP2)Inventory.h"

class Player : public GameObject
{
public:
    Player(string name, string race, int moneyAmount, Position pos);
    ~Player();

    void addItem(string itemName);
    void removeItem(string itemName);

    void takeDamage(int damageTaken);
    void healHealth(int amountHealed);

    bool ifDead();
    
private:
    string race;
    Inventory playerInventory;
    int health;
};

#endif
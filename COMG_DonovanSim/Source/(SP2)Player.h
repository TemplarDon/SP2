#ifndef PLAYER_H
#define PLAYER_H

#include "(SP2)GameObject.h"
#include "(SP2)Inventory.h"
#include "Camera.h"

class Player : public GameObject
{
public:
    Player();
    Player(string name, string race, int moneyAmount, Position pos);
    ~Player();

    void addItem(string itemName);
    void removeItem(string itemName);

    void takeDamage(int damageTaken);
    void healHealth(int amountHealed);

    string getCameraType();
    Camera* getCameraPtr();
    void setCameraPtr(Camera someCamera);
    void setCameraType(string someCamType);

    void setPlayerStats(string name, string race, int moneyAmount, Position pos, Camera someCamera);

    bool ifDead();
    
private:
    string race;
    Inventory playerInventory;
    int health;
    string cameraType;
    Camera* cameraPtr;
};

#endif
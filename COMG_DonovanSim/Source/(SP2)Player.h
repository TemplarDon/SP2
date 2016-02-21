/*************************************************************************************************/
/*!
\file   Player.h
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Header File for the Player Class, contains player stats
*/
/*************************************************************************************************/
#ifndef PLAYER_H
#define PLAYER_H

#include "(SP2)InteractableOBJs.h"
#include "(SP2)Inventory.h"
#include "(SP2)Ship.h"
#include "Camera.h"

/*************************************************************************************************/
/*!
Class Player : public GameObject
\brief
    Class Player. Contains Constructor/ Destructor for Player and player stats
*/
/*************************************************************************************************/
class Player : public GameObject
{
public:
    Player();
    Player(string name, string race, int moneyAmount, Position pos);
    ~Player();

    // Functions for adding and removing items from players inventory
    void addItem(InteractableOBJs itemName);
    void removeItem(InteractableOBJs itemName);

    // Functions for player taking damage and healing health
    void takeDamage(int damageTaken);
    void healHealth(int amountHealed);

    // Functions for get which camera player is currently using
    string getCameraType();
    Camera* getCameraPtr();

    // Functions for setting which camera for player to use
    void setCameraPtr(Camera someCamera);
    void setCameraType(string someCamType);

    // Function to set player stats
    void setPlayerStats(string name, string race, int moneyAmount, Position pos, Camera someCamera);

    // Check if player is dead
    bool ifDead();
    
private:

    // Race of player Eg. Human / Alien
    string race;

    // Inventory of Player
    Inventory playerInventory;

    // Health of Player
    int health;

    // String containing either "first" or "third", where "first" refers to first person camera and "third" refers to third person camera
    string cameraType;

    // Camera Pointer to access Camera values
    Camera* cameraPtr;
};

#endif
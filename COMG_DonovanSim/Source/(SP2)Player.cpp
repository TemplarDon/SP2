/*************************************************************************************************/
/*!
\file   Player.cpp
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Contains code for Player class
*/
/*************************************************************************************************/
#include "(SP2)Player.h"

/******************************************************************************/
/*!
\brief
    Player Constructor
*/
/******************************************************************************/
Player::Player() : GameObject("", Position(0, 0, 0)), health(100), cameraType("first"), cameraPtr(0)
{

}

/******************************************************************************/
/*!
\brief
    Player Destructor
*/
/******************************************************************************/
Player::~Player()
{
}

/******************************************************************************/
/*!
\brief
    Function for adding item to player's inventory

\param  itemName
    InteractableOBJs containing item's name that is to be added
*/
/******************************************************************************/
void Player::addItem(InteractableOBJs itemName)
{
    this->playerInventory.itemList.push_back(itemName);
}

/******************************************************************************/
/*!
\brief
    Function for removing an item from player's inventory

\param  itemName
    InteractableOBJs containing item's name that is to be removed
*/
/******************************************************************************/
void Player::removeItem(InteractableOBJs itemName)
{
    for (list<InteractableOBJs>::iterator it = this->playerInventory.itemList.begin(); it != this->playerInventory.itemList.end();)
    {
        if (it->name == itemName.name)
        {
            it = this->playerInventory.itemList.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

/******************************************************************************/
/*!
\brief
    Function for player taking damage

\param  damageTaken
    int of damage the player will take
*/
/******************************************************************************/
void Player::takeDamage(int damageTaken)
{
    this->health -= damageTaken;
}

/******************************************************************************/
/*!
\brief
    Function for player healing health

\param  amountHealed
    int of damage the player will be healed for
*/
/******************************************************************************/
void Player::healHealth(int amountHealed)
{
    this->health += amountHealed;
}

/******************************************************************************/
/*!
\brief
    Function for getting Player's camera type (a string)

\return  
    returns a string of either "first" or "third", where "first" means first-person camera and so on
*/
/******************************************************************************/
string Player::getCameraType()
{
    return this->cameraType;
}

/******************************************************************************/
/*!
\brief
    Function for getting Player's camera pointer

\return
    returns a camera pointer
*/
/******************************************************************************/
Camera* Player::getCameraPtr()
{
    return cameraPtr;
}

/******************************************************************************/
/*!
\brief
    Function for setting Player's camera pointer

\param  someCamera
    a camera
*/
/******************************************************************************/
void Player::setCameraPtr(Camera someCamera)
{
    this->cameraPtr = &someCamera;
}

/******************************************************************************/
/*!
\brief
    Function for setting Player's camera type

\param  someCamType
    a string that contains either "first" or "third", where "first" means first-person camera and so on
*/
/******************************************************************************/
void Player::setCameraType(string someCamType)
{
    this->cameraType = someCamType;
}


/******************************************************************************/
/*!
\brief
    Function for setting Player's stats

\param  name
    player's name
\param  race
    player's race
\param  moneyAmount
    player's money, set his current amount to this
\param  pos
    player's pos
\param  someCamera
    player's camera
*/
/******************************************************************************/
void Player::setPlayerStats(string name, string race, int moneyAmount, Position pos, Camera someCamera)
{
    this->name = name;
    this->race = race;
    this->pos = pos;
    this->playerInventory.addMoney(100);
    this->cameraPtr = &someCamera;
}

/******************************************************************************/
/*!
\brief
    Function for checking if player is dead

\return  
    returns bool, true if dead
*/
/******************************************************************************/
bool Player::ifDead()
{
    if (this->health <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
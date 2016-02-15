#include "(SP2)Player.h"

Player::Player(string name, string race) : GameObject(name), race(race)
{
}

Player::~Player()
{
}

void Player::addItem(string itemName)
{
    this->playerInventory.itemList.push_back(itemName);
}

void Player::removeItem(string itemName)
{
    for (list<string>::iterator it = this->playerInventory.itemList.begin(); it != this->playerInventory.itemList.end();)
    {
        if (*it == itemName)
        {
            it = this->playerInventory.itemList.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
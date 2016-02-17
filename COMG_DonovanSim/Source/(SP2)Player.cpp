#include "(SP2)Player.h"

Player::Player(string name, string race, int moneyAmount, Position pos) : GameObject(name, pos), race(race), health(100)
{
    playerInventory.addMoney(moneyAmount);
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

void Player::takeDamage(int damageTaken)
{
    this->health -= damageTaken;
}

void Player::healHealth(int amountHealed)
{
    this->health += amountHealed;
}

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
#include "(SP2)Player.h"

//Player::Player(string name, string race, int moneyAmount, Position pos) : GameObject(name, pos), race(race), health(100), cameraType("first")
//{
//    playerInventory.addMoney(moneyAmount);
//}

Player::Player() : GameObject("", Position(0, 0, 0)), health(100), cameraType("first"), cameraPtr(0)
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

void Player::takeDamage(int damageTaken)
{
    this->health -= damageTaken;
}

void Player::healHealth(int amountHealed)
{
    this->health += amountHealed;
}

string Player::getCameraType()
{
    return this->cameraType;
}

Camera* Player::getCameraPtr()
{
    return cameraPtr;
}

void Player::setCameraPtr(Camera someCamera)
{
    this->cameraPtr = &someCamera;
}

void Player::setCameraType(string someCamType)
{
    this->cameraType = someCamType;
}

void Player::setPlayerStats(string name, string race, int moneyAmount, Position pos, Camera someCamera)
{
    this->name = name;
    this->race = race;
    this->pos = pos;
    this->playerInventory.addMoney(100);
    this->cameraPtr = &someCamera;
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
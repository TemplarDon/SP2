#include "(SP2)GameObject.h"

GameObject::GameObject(std::string name, Position pos)
{ 
    this->name = name;
    this->pos = pos;
}

GameObject::~GameObject()
{
}
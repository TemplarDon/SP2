/*************************************************************************************************/
/*!
\file   GameObject.cpp
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
Contains code for GameObject class
*/
/*************************************************************************************************/
#include "(SP2)GameObject.h"

/******************************************************************************/
/*!
\brief
    GameObject Constructor
\param  name
    name of GameObject
\param  pos
    position of GameObject
*/
/******************************************************************************/
GameObject::GameObject(std::string name, Position pos)
{ 
    this->name = name;
    this->pos = pos;
}

/******************************************************************************/
/*!
\brief
    GameObject Destructor
*/
/******************************************************************************/
GameObject::~GameObject()
{
}
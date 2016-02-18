/*************************************************************************************************/
/*!
\file   GameObject.h
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Header File for the GameObject Abstract Base Class
*/
/*************************************************************************************************/
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "vertex.h"
#include <string>
#include <vector>
#include <list>

using std::string;
using std::vector;
using std::list;

/*************************************************************************************************/
/*!
Class GameObject 
\brief
    Class GameObject. Contains Constructor/ Destructor for GameObject, name of object and position of object
*/
/*************************************************************************************************/
class GameObject
{
private:
    

protected:
    GameObject(std::string name, Position pos);

public:
    // Name of object
    string name;

    // Position of Object
    Position pos;

    virtual ~GameObject();
    
};

#endif
/*************************************************************************************************/
/*!
\file   Engine.h
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Header File for the Engine Class, with parent class ShipParts
*/
/*************************************************************************************************/
#ifndef ENGINE_H
#define ENGINE_H

#include "ShipParts.h"

/*************************************************************************************************/
/*!
Class Engine : public ShipParts
\brief
Class Engine, with parent class ShipParts. Contains Constructor/ Destructor for Engine
*/
/*************************************************************************************************/
class Engine : public ShipParts
{
public:
    Engine(string name);
    ~Engine();

    virtual float partsEffect();
protected:

};

#endif
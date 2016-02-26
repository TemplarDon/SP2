/*************************************************************************************************/
/*!
\file   Engine.cpp
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Contains code for Engine class
*/
/*************************************************************************************************/
#include "Engine.h"

/******************************************************************************/
/*!
\brief
    Engine Constructor
\param  name
    name of Engine
*/
/******************************************************************************/
Engine::Engine(string name) : ShipParts(name)
{
}

/******************************************************************************/
/*!
\brief
    Engine Destructor
*/
/******************************************************************************/
Engine::~Engine()
{
}

/******************************************************************************/
/*!
\brief
    Function for the partsEffect
\return
    returns a value that is used to increase the ship's stats
*/
/******************************************************************************/
float Engine::partsEffect()
{
    return 0;
}
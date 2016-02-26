/*************************************************************************************************/
/*!
\file   Wings.cpp
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Contains code for Wings class
*/
/*************************************************************************************************/
#include "Wings.h"

/******************************************************************************/
/*!
\brief
    Wings Constructor
\param  name
    name of Wing Object
*/
/******************************************************************************/
Wings::Wings(string name) : ShipParts(name)
{
}

/******************************************************************************/
/*!
\brief
    Wings Destructor
*/
/******************************************************************************/
Wings::~Wings()
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
float Wings::partsEffect()
{
    return 0;
}
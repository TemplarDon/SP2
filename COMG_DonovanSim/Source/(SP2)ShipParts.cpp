/*************************************************************************************************/
/*!
\file   ShipParts.cpp
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Contains code for ShipParts class and functions
*/
/*************************************************************************************************/
#include "(SP2)ShipParts.h"

/******************************************************************************/
/*!
\brief
    ShipBuilder Constructor
\param  name
    name of the Ship Part
*/
/******************************************************************************/
ShipParts::ShipParts(string name) : name(name)
{
}

/******************************************************************************/
/*!
\brief
    ShipBuilder Destructor
*/
/******************************************************************************/
ShipParts::~ShipParts()
{
}

/******************************************************************************/
/*!
\brief
    Function for getting name of Ship Part
\return
    returns a string containing the name of the Ship Part
*/
/******************************************************************************/
string ShipParts::getName()
{
    return this->name;
}

/******************************************************************************/
/*!
\brief
    Function for the partsEffect
\return
    returns 0
*/
/******************************************************************************/
int ShipParts::partsEffect()
{
    return 0;
}
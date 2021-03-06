/*************************************************************************************************/
/*!
\file   Hull.cpp
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Contains code for Hull class
*/
/*************************************************************************************************/
#include "Hull.h"

/******************************************************************************/
/*!
\brief
    Hull Constructor
\param  name
    name of Hull
*/
/******************************************************************************/
Hull::Hull(string name) : ShipParts(name)
{

}

/******************************************************************************/
/*!
\brief
    Hull Destructor
*/
/******************************************************************************/
Hull::~Hull()
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
float Hull::partsEffect()
{
    return 0;
}
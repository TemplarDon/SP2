/*************************************************************************************************/
/*!
\file   Inventory.cpp
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Contains code for Inventory class
*/
/*************************************************************************************************/
#include "Inventory.h"

/******************************************************************************/
/*!
\brief
    Inventory Constructor
*/
/******************************************************************************/
Inventory::Inventory()
{
}

/******************************************************************************/
/*!
\brief
    Inventory Destructor
*/
/******************************************************************************/
Inventory::~Inventory()
{
}

/******************************************************************************/
/*!
\brief
    Function for adding crystals to player

\param  crystalsNum
    amount of crystals to be added
*/
/******************************************************************************/
void Inventory::addCrystals(int crystalsNum)
{
    this->crystalAmount += crystalsNum;
}

/******************************************************************************/
/*!
\brief
Function for getting crystals to player

\return  
    amount of crystals player inventory has
*/
/******************************************************************************/
int Inventory::getCrystalsAmount()
{
    return this->crystalAmount;
}
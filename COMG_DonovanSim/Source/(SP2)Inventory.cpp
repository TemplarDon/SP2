/*************************************************************************************************/
/*!
\file   Inventory.cpp
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Contains code for Inventory class
*/
/*************************************************************************************************/
#include "(SP2)Inventory.h"

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
    Function for adding money to player

\param  money
    amount of money to be added
*/
/******************************************************************************/
void Inventory::addMoney(int money)
{
    this->moneyAmount += money;
}
/*************************************************************************************************/
/*!
\file   Inventory.h
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Header File for the Inventory Class, used for holding players' money and items
*/
/*************************************************************************************************/
#ifndef INVENTORY_H
#define INVENTORY_H
#include "InteractableOBJs.h"
#include "ShipParts.h"

/*************************************************************************************************/
/*!
Class Inventory : 
\brief
    Class Inventory. Contains Constructor/ Destructor for Inventory, players' moneyAmount and itemList
*/
/*************************************************************************************************/
class Inventory
{
public:
    Inventory();
    ~Inventory();

    // List containing Items
    list<InteractableOBJs> itemList;
    list<ShipParts> shipPartsList;

    // Function to add crystals to Player
    void addCrystals(int crystalsNum);
    
    // Function to get amount of crystals
    int getCrystalsAmount();

private:

    // Crystal Amount
    int crystalAmount;

};

#endif
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
#include "(SP2)GameObject.h"

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

    // Money Amount
    int moneyAmount;

    // List containing Items
    list<string> itemList;

    // Function to add Money to Player
    void addMoney(int money);
    
private:


};

#endif
/*************************************************************************************************/
/*!
\file   Ship_Upgrade.h
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Header File for the Ship_Upgrade Class
*/
/*************************************************************************************************/
#ifndef SHIP_UPGRADE_H
#define SHIP_UPGARDE_H

#include <string>
using std::string;

/*************************************************************************************************/
/*!
Class Ship_Upgrade
\brief
    Class Ship_Upgrade. Contains Constructor/ Destructor for Ship_Upgrade
*/
/*************************************************************************************************/
class Ship_Upgrade
{
protected:
    Ship_Upgrade(string name);
    
    // Ship's name
    string name;

    // Virtual function for using upgrade's effect
    virtual void useUpgradeEffect();

public:

    ~Ship_Upgrade();

};

#endif
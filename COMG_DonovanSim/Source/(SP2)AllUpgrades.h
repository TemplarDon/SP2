/*************************************************************************************************/
/*!
\file   AllUpgrades.h
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
Header File for Containing all Different Upgrades for the Ship
*/
/*************************************************************************************************/
#ifndef ALL_UPGRADES_H
#define ALL_UPGARDES_H

#include "(SP2)Ship_Upgrade.h"

/*************************************************************************************************/
/*!
Class Nitro_Boost : public Ship_Upgrade
\brief  Class Nitro_Boost, with parent class Ship_Upgarde, contains the useUpgradeEffect() function that will activate some effect (not implemented yet)
*/
/*************************************************************************************************/
class Nitro_Boost : public Ship_Upgrade
{
public:
    Nitro_Boost();
    ~Nitro_Boost();

    void useUpgradeEffect();
};

#endif
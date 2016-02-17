#ifndef ALL_UPGRADES_H
#define ALL_UPGARDES_H

#include "(SP2)Ship_Upgrade.h"

class Nitro_Boost : public Ship_Upgrade
{
public:
    Nitro_Boost();
    ~Nitro_Boost();

    void useUpgradeEffect();
};

#endif
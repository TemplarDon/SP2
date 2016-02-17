#ifndef ALL_PARTS_H
#define ALL_PARTS_H

#include "(SP2)ShipParts.h"

class Dual_Wings : public ShipParts
{
    Dual_Wings(string name);
    ~Dual_Wings();

    void partsEffect();
};

class Quad_Wings : public ShipParts
{
    Quad_Wings(string name);
    ~Quad_Wings();

    void partsEffect();
};

class G1_Engine : public ShipParts
{
    G1_Engine(string name);
    ~G1_Engine();

    void partsEffect();
};

class G2_Engine : public ShipParts
{
    G2_Engine(string name);
    ~G2_Engine();

    void partsEffect();
};

class Light_Hull : public ShipParts
{
    Light_Hull(string name);
    ~Light_Hull();

    void partsEffect();
};

class Medium_Hull : public ShipParts
{
    Medium_Hull(string name);
    ~Medium_Hull();

    void partsEffect();
};


class Heavy_Hull : public ShipParts
{
    Heavy_Hull(string name);
    ~Heavy_Hull();

    void partsEffect();
};



#endif
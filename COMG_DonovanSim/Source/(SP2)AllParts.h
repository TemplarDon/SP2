#ifndef ALL_PARTS_H
#define ALL_PARTS_H

#include "(SP2)Wings.h"
#include "(SP2)Engine.h"
#include "(SP2)Hull.h"

class Dual_Wings : public Wings
{
public:
    Dual_Wings(string name);
    ~Dual_Wings();

    int partsEffect();
};

class Quad_Wings : public Wings
{
public:
    Quad_Wings(string name);
    ~Quad_Wings();

    int partsEffect();
};

class G1_Engine : public Engine
{
public:
    G1_Engine(string name);
    ~G1_Engine();

    int partsEffect();
};

class G2_Engine : public Engine
{
public:
    G2_Engine(string name);
    ~G2_Engine();

    int partsEffect();
};

class Light_Hull : public Hull
{
public:
    Light_Hull(string name);
    ~Light_Hull();

    int partsEffect();
};

class Medium_Hull : public Hull
{
public:
    Medium_Hull(string name);
    ~Medium_Hull();

    int partsEffect();
};


class Heavy_Hull : public Hull
{
public:
    Heavy_Hull(string name);
    ~Heavy_Hull();

    int partsEffect();
};



#endif
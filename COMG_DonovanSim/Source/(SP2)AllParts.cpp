#include "(SP2)AllParts.h"

Dual_Wings::Dual_Wings(string name) : Wings(name)
{
}

Dual_Wings::~Dual_Wings()
{
}

int Dual_Wings::partsEffect()
{
    return 3;
}


Quad_Wings::Quad_Wings(string name) : Wings(name)
{
}

Quad_Wings::~Quad_Wings()
{
}

int Quad_Wings::partsEffect()
{
    return 5;
}


G1_Engine::G1_Engine(string name) : Engine(name)
{
}

G1_Engine::~G1_Engine()
{
}

int G1_Engine::partsEffect()
{
    return 3;
}


G2_Engine::G2_Engine(string name) : Engine(name)
{
}

G2_Engine::~G2_Engine()
{
}

int G2_Engine::partsEffect()
{
    return 5;
}


Light_Hull::Light_Hull(string name) : Hull(name)
{
}

Light_Hull::~Light_Hull()
{
}

int Light_Hull::partsEffect()
{
    return 0;
}


Medium_Hull::Medium_Hull(string name) : Hull(name)
{
}

Medium_Hull::~Medium_Hull()
{
}

int Medium_Hull::partsEffect()
{
    return 0;
}


Heavy_Hull::Heavy_Hull(string name) : Hull(name)
{
}

Heavy_Hull::~Heavy_Hull()
{
}

int Heavy_Hull::partsEffect()
{
    return 0;
}



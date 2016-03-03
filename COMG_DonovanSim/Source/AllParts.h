/*************************************************************************************************/
/*!
\file   AllParts.h
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
Header File for Containing all Different Parts for the Ship
*/
/*************************************************************************************************/

#ifndef ALL_PARTS_H
#define ALL_PARTS_H

#include "Wings.h"
#include "Engine.h"
#include "Hull.h"

/*************************************************************************************************/
/*!
Class Dual_Wings : public Wings
\brief  Class Dual_Wings, with parent class Wings, contains the partsEffect() function that returns a int to use for increasing the ship's stats
*/
/*************************************************************************************************/
class Dual_Wings : public Wings
{
public:
    Dual_Wings(string name = "DualWings");
    ~Dual_Wings();

    virtual float partsEffect();
};

/*************************************************************************************************/
/*!
Class Quad_Wings : public Wings
\brief  Class Quad_Wings, with parent class Wings, contains the partsEffect() function that returns a int to use for increasing the ship's stats
*/
/*************************************************************************************************/
class Quad_Wings : public Wings
{
public:
    Quad_Wings(string name = "QuadWings");
    ~Quad_Wings();

    virtual float partsEffect();
};

/*************************************************************************************************/
/*!
Class G1_Engine : public Engine
\brief  Class G1_Engine, with parent class Engine, contains the partsEffect() function that returns a int to use for increasing the ship's stats
*/
/*************************************************************************************************/
class G1_Engine : public Engine
{
public:
    G1_Engine(string name = "G1Engine");
    ~G1_Engine();

    virtual float partsEffect();
};

/*************************************************************************************************/
/*!
Class G2_Engine : public Engine
\brief  Class G2_Engine, with parent class Engine, contains the partsEffect() function that returns a int to use for increasing the ship's stats
*/
/*************************************************************************************************/
class G2_Engine : public Engine
{
public:
    G2_Engine(string name = "G2Engine");
    ~G2_Engine();

    virtual float partsEffect();
};

/*************************************************************************************************/
/*!
Class Light_Hull : public Hull
\brief  Class Light_Hull, with parent class Hull, contains the partsEffect() function that returns a int to use for increasing the ship's stats
*/
/*************************************************************************************************/
class Light_Hull : public Hull
{
public:
    Light_Hull(string name = "LightHull");
    ~Light_Hull();

    virtual float partsEffect();
};

/*************************************************************************************************/
/*!
Class Medium_Hull : public Hull
\brief  Class Medium_Hull, with parent class Hull, contains the partsEffect() function that returns a int to use for increasing the ship's stats
*/
/*************************************************************************************************/
class Medium_Hull : public Hull
{
public:
    Medium_Hull(string name = "MediumHull");
    ~Medium_Hull();

    virtual float partsEffect();
};

/*************************************************************************************************/
/*!
Class Large_Hull : public Hull
\brief  Class Large_Hull, with parent class Hull, contains the partsEffect() function that returns a int to use for increasing the ship's stats
*/
/*************************************************************************************************/
class Large_Hull : public Hull
{
public:
    Large_Hull(string name = "LargeHull");
    ~Large_Hull();

    virtual float partsEffect();
};



#endif
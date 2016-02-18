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

#include "(SP2)Wings.h"
#include "(SP2)Engine.h"
#include "(SP2)Hull.h"

/*************************************************************************************************/
/*!
Class Dual_Wings : public Wings
\brief  Class Dual_Wings, with parent class Wings, contains the partsEffect() function that returns a int to use for increasing the ship's stats
*/
/*************************************************************************************************/
class Dual_Wings : public Wings
{
public:
    Dual_Wings(string name);
    ~Dual_Wings();

    int partsEffect();
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
    Quad_Wings(string name);
    ~Quad_Wings();

    int partsEffect();
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
    G1_Engine(string name);
    ~G1_Engine();

    int partsEffect();
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
    G2_Engine(string name);
    ~G2_Engine();

    int partsEffect();
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
    Light_Hull(string name);
    ~Light_Hull();

    int partsEffect();
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
    Medium_Hull(string name);
    ~Medium_Hull();

    int partsEffect();
};

/*************************************************************************************************/
/*!
Class Heavy_Hull : public Hull
\brief  Class Heavy_Hull, with parent class Hull, contains the partsEffect() function that returns a int to use for increasing the ship's stats
*/
/*************************************************************************************************/
class Heavy_Hull : public Hull
{
public:
    Heavy_Hull(string name);
    ~Heavy_Hull();

    int partsEffect();
};



#endif
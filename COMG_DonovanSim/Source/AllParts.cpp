/*************************************************************************************************/
/*!
\file   AllParts.cpp
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
Contains code for initialising every ship part and the part's effect on the ship
*/
/*************************************************************************************************/
#include "AllParts.h"

/******************************************************************************/
/*!
\brief
    Dual_Wings Constructor

\param  name
    name of Dual_Wings Part (Eg. Dual Wings)
*/
/******************************************************************************/
Dual_Wings::Dual_Wings(string name) : Wings(name)
{
}

/******************************************************************************/
/*!
\brief
    Dual_Wings Destructor
*/
/******************************************************************************/
Dual_Wings::~Dual_Wings()
{
}

/******************************************************************************/
/*!
\brief
    Function for getting a number used to increase certain ship stats

\return  
    returns an float that is used to increase certain ship stats
*/
/******************************************************************************/
float Dual_Wings::partsEffect()
{
    return 50;
}

/******************************************************************************/
/*!
\brief
    Quad_Wings Constructor

\param  name
    name of Quad_Wings Part (Eg. Quad Wings)
*/
/******************************************************************************/
Quad_Wings::Quad_Wings(string name) : Wings(name)
{
}

/******************************************************************************/
/*!
\brief
    Quad_Wings Destructor
*/
/******************************************************************************/
Quad_Wings::~Quad_Wings()
{
}

/******************************************************************************/
/*!
\brief
    Function for getting a number used to increase certain ship stats

\return  
    returns an float that is used to increase certain ship stats
*/
/******************************************************************************/
float Quad_Wings::partsEffect()
{
    return 60;
}

/******************************************************************************/
/*!
\brief
    G1_Engine Constructor

\param  name
    name of G1_Engine Part (Eg. G1 Engine)
*/
/******************************************************************************/
G1_Engine::G1_Engine(string name) : Engine(name)
{
}

/******************************************************************************/
/*!
\brief
    G1_Engine Destructor
*/
/******************************************************************************/
G1_Engine::~G1_Engine()
{
}

/******************************************************************************/
/*!
\brief
    Function for getting a number used to increase certain ship stats

\return  
    returns an float that is used to increase certain ship stats
*/
/******************************************************************************/
float G1_Engine::partsEffect()
{
    return 3;
}

/******************************************************************************/
/*!
\brief
    G2_Engine Constructor

\param  name
    name of G2_Engine Part (Eg. G2 Engine)
*/
/******************************************************************************/
G2_Engine::G2_Engine(string name) : Engine(name)
{
}

/******************************************************************************/
/*!
\brief
    G2_Engine Destructor
*/
/******************************************************************************/
G2_Engine::~G2_Engine()
{
}

/******************************************************************************/
/*!
\brief
    Function for getting a number used to increase certain ship stats

\return
    returns an float that is used to increase certain ship stats
*/
/******************************************************************************/
float G2_Engine::partsEffect()
{
    return 5;
}

/******************************************************************************/
/*!
\brief
    Light_Hull Constructor

\param  name
    name of Light_Hull Part (Eg. Light Hull)
*/
/******************************************************************************/
Light_Hull::Light_Hull(string name) : Hull(name)
{
}

/******************************************************************************/
/*!
\brief
    Light_Hull Destructor
*/
/******************************************************************************/
Light_Hull::~Light_Hull()
{
}

/******************************************************************************/
/*!
\brief
    Function for getting a number used to increase certain ship stats
    
\return
    returns an float that is used to increase certain ship stats
*/
/******************************************************************************/
float Light_Hull::partsEffect()
{
    return 15;
}

/******************************************************************************/
/*!
\brief
    Medium_Hull Constructor

\param  name
    name of Medium_Hull Part (Eg. Medium Hull)
*/
/******************************************************************************/
Medium_Hull::Medium_Hull(string name) : Hull(name)
{
}

/******************************************************************************/
/*!
\brief
    Medium_Hall Destructor
*/
/******************************************************************************/
Medium_Hull::~Medium_Hull()
{
}

/******************************************************************************/
/*!
\brief
    Function for getting a number used to increase certain ship stats

\return
    returns an float that is used to increase certain ship stats
*/
/******************************************************************************/
float Medium_Hull::partsEffect()
{
    return 8;
}

/******************************************************************************/
/*!
\brief
    Heavy_Hull Constructor

\param  name
    name of Heavy_Hull Part (Eg. Heavy Hull)
*/
/******************************************************************************/
Large_Hull::Large_Hull(string name) : Hull(name)
{
}

/******************************************************************************/
/*!
\brief
    Heavy_Hull Destructor
*/
/******************************************************************************/
Large_Hull::~Large_Hull()
{
}

/******************************************************************************/
/*!
\brief
    Function for getting a number used to increase certain ship stats

\return
    returns an float that is used to increase certain ship stats
*/
/******************************************************************************/
float Large_Hull::partsEffect()
{
    return 3;
}



/*************************************************************************************************/
/*!
\file   Hull.h
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
Header File for the Hull Class, with parent class ShipParts
*/
/*************************************************************************************************/
#ifndef HULL_H
#define HULL_H

#include "ShipParts.h"

/*************************************************************************************************/
/*!
Class Hull : public ShipParts
\brief
    Class Hull, with parent class ShipParts. Contains Constructor/ Destructor for Hull
*/
/*************************************************************************************************/
class Hull : public ShipParts
{
public:
    Hull(string name);
    ~Hull();

    virtual float partsEffect();
protected:

};

#endif
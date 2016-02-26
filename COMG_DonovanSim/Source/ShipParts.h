/*************************************************************************************************/
/*!
\file   ShipParts.h
\author Donovan Sim Yew Wee
\par    email:donovandenzel@gmail.com
\brief
    Header File for the ShipParts Class
*/
/*************************************************************************************************/
#ifndef SHIP_PARTS_H
#define SHIP_PARTS_H

#include <string>
using std::string;

/*************************************************************************************************/
/*!
Class ShipParts
\brief
    Class ShipParts. Contains Constructor/ Destructor for ShipParts and a virtual function, for the parts' effect
*/
/*************************************************************************************************/
class ShipParts
{
protected:
    ShipParts(string name);
    string name;


public:
    virtual float partsEffect() = 0;
    string getName();
    ~ShipParts();

};


#endif
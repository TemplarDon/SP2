/*************************************************************************************************/
/*!
\file   Inventory.h
\author Gary Goh
\brief
Header File for the Keypad Class, used for creating the keypad interaction
*/
/*************************************************************************************************/
#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#include "InteractableOBJs.h"
#include "ClassTarget.h"

/*************************************************************************************************/
/*!
Class Keypad :
\brief
    Class Keypad. Contains Constructor/ Destructor for Keypad, its pos and orientation
*/
/*************************************************************************************************/
class Keypad
{
public:
	Position pos;
	float orientation;
	ClassTarget<bool> targetBool;

	Keypad(Position pos = { 0, 0, 0 }, float orientation = 0)
		: pos(pos), orientation(orientation), targetBool()
	{
	}
};

#endif
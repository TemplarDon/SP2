#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#include "InteractableOBJs.h"
#include "ClassTarget.h"

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
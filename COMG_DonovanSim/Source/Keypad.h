#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#include "InteractableOBJs.h"

class Keypad
{
public:
	Position pos;
	float orientation;

	Keypad(Position pos, float orientation);
};

#endif
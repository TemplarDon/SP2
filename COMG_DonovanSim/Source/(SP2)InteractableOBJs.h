#ifndef INTERACTABLE_OBJ_H
#define INTERACTABLE_OBJ_H

#include "(SP2)CollisionOBJs.h"

class InteractableOBJs : public CollisionOBJs
{
public:
    InteractableOBJs(string name, Position maxPos, Position minPos, Position offSet, int scaleOffSet, float rotateAngle, Vector3 rotateAxis);
    ~InteractableOBJs();

	bool isInView(const Position &pos, const Vector3 &viewDirection);
private:
	float requiredFocusSquared;
	float requiredDistanceSquared;
};

#endif
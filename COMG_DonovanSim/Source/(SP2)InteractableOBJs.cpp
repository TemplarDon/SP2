#include "(SP2)InteractableOBJs.h"

InteractableOBJs::InteractableOBJs(string name, Position maxPos, Position minPos, Position offSet, int scaleOffSet, float rotateAngle, Vector3 rotateAxis)
: CollisionOBJs(name, maxPos, minPos, offSet, scaleOffSet, rotateAngle, rotateAxis)
{
}

InteractableOBJs::~InteractableOBJs()
{

}

bool InteractableOBJs::isInView(const Position &charPos, const Vector3 &viewDirection)
{
	Vector3 P1 = Vector3(charPos.x, charPos.y, charPos.z);
	Vector3 P2 = Vector3(pos.x, pos.y, pos.z);

	Vector3 D = P2 - P1;

	std::cout << (D - D.Dot(viewDirection)*viewDirection).LengthSquared() << std::endl;
	//Check if within distance
	if (D.LengthSquared() > requiredDistanceSquared) return false;

	//Check if focusing on point

	std::cout << "Is near" << std::endl;
	return (D - D.Dot(viewDirection)*viewDirection).LengthSquared() < requiredDistanceSquared;
	
}

void ttttttt()
{

}
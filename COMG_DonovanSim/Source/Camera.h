#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
//#include "(SP2)Player.h"
//#include "(SP2)InteractableOBJs.h"
//#include "(SP2)Building.h"

class Camera
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;

	Camera();
	~Camera();
	void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	void Reset();
	void Update(double dt);

    
};

#endif
#ifndef CAMERA_5_H
#define CAMERA_5_H

#include "Camera.h"

#include "(SP2)Building.h"
#include "(SP2)InteractableOBJs.h"

class Camera5 : public Camera
{
public:
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;

	Camera5();
	~Camera5();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
    virtual void Update(double dt, std::vector<InteractableOBJs>&InteractablesList, std::vector<Building>&BuildingsList);
	virtual void Reset();
	float horizontalAngle = 0;
	float verticalAngle = 0;
	float mouseSpeed;
	float speed;

    bool canMove;
};

#endif
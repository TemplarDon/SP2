/*************************************************************************************************/
/*!
\file   FirstPersonCamera.h
\brief
Header File for the FirstPersonCamera Class, with parent class Camera
*/
/*************************************************************************************************/
#ifndef CAMERA_5_H
#define CAMERA_5_H

#include "Camera.h"

#include "Building.h"
#include "InteractableOBJs.h"
#include "Player.h"

/*************************************************************************************************/
/*!
Class FirstPersonCamera : public Camera
\brief
    Class FirstPersonCamera, with parent class Camera. Contains Constructor/ Destructor for FirstPersonCamera and functions for collision detection
*/
/*************************************************************************************************/
class FirstPersonCamera : public Camera
{
public:
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;

	FirstPersonCamera();
	~FirstPersonCamera();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
    virtual void Update(double dt, std::vector<InteractableOBJs>&InteractablesList, std::vector<Building>&BuildingsList, Player &somePlayer);
	virtual void Reset();
	float horizontalAngle = 0;
	float verticalAngle = 0;
	float mouseSpeed;
	float speed;

    bool canMoveBuilding;       // bool to check if camera can move through every obj in BuildingList vector
    bool canMoveInteractable;   // bool to check if camera can move through every obj in InteractableList vector

    bool createBoundary(std::vector<InteractableOBJs>&InteractablesList, std::vector<Building>&BuildingsList, Player &somePlayer, Position camPos);
};

#endif
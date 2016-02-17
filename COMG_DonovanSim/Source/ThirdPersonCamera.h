#ifndef _THIRDPERSONCAMERA_H_
#define _THIRDPERSONCAMERA_H_

#include "Camera.h"
#include "Vertex.h"

#include "MyMath.h"

#include "(SP2)Player.h"
#include "(SP2)Building.h"
#include "(SP2)InteractableOBJs.h"

class ThirdPersonCamera : public Camera
{
private:
	float camDistance;
	Position *focus;
	float minDistance;
	float maxDistance;
	float minPitch;
	float maxPitch;

public:
	Vector3 camDirection;

	ThirdPersonCamera();
	~ThirdPersonCamera();
	virtual void Init(const Vector3 position, const Vector3 up, Position *focus, const float camDistance);
    virtual void Update(double dt, vector<InteractableOBJs>&InteractablesList, vector<Building>&BuildingsList, Player &somePlayer);

	void YawCamera(const float degrees);
	void PitchCamera(float degrees);
	void Refocus();

	float GetCameraDistance();
	void SetCameraDistanceAbsolute(float distance);
	void SetCameraDistanceRelative(float distance);
	void SetCameraDistanceBounds(float min, float max);

	float GetCameraPitch();
	void SetCameraPitchBounds(float min, float max);

	Position* GetFocusPoint();
	void SetFocusPoint(Position *focus);

    void cameraMovement(double dt, vector<InteractableOBJs>&InteractablesList, vector<Building>&BuildingsList, Player &somePlayer);

    bool canMoveInteractable;
    bool canMoveBuilding;
};

#endif
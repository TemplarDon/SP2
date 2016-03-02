#ifndef _THIRDPERSONCAMERA_H_
#define _THIRDPERSONCAMERA_H_

#include "Camera.h"
#include "Vertex.h"

#include "MyMath.h"

#include "Player.h"
#include "Building.h"
#include "Ship.h"

class ThirdPersonCamera : public Camera
{
private:
	float camDistance;
	Position *focus;
	float minDistance;
	float maxDistance;
	float minPitch;
	float maxPitch;
	bool mouseEnabled;

	Vector3 yawBoundsDirection; //Direction is based on xz-plane.
	float yawBoundsRange; //In degrees from 0 to 180.

public:
    // Default Values to check if ship is pitching / yawing
    Vector3 defaultRightVec;
    Vector3 defaultUpVec;

	Vector3 camDirection;

	ThirdPersonCamera();
	~ThirdPersonCamera();
	virtual void Init(const Vector3 position, const Vector3 up, Position *focus, const float camDistance);
    virtual void Update(double dt, vector<InteractableOBJs>&InteractablesList, vector<Building>&BuildingsList, Player &somePlayer);

	void SetMouseEnabled(const bool &toggle);

	void YawCamera(float degrees);
	void PitchCamera(float degrees);
	void Refocus();

	float GetCameraDistance();
	void SetCameraDistanceAbsolute(float distance);
	void SetCameraDistanceRelative(float distance);
	void SetCameraDistanceBounds(float min, float max);

	float GetCameraPitch();
	void SetCameraPitchBounds(float min, float max);

	void SetCameraYawBounds(Vector3 direction, float range);
	void SetCameraYawBounds(float boundsLeft, float boundsRight);

	void RotateYawBoundsDirection(float degrees);

	Position* GetFocusPoint();
	void SetFocusPoint(Position *focus);

    // Variables for checking for collision
    bool canMoveInteractable;
    bool canMoveBuilding;

    // Variables for checking where ship is turning
    bool yawingRight;
    bool yawingLeft;
    bool pitchingUp;
    bool pitchingDown;

    // Function for checking which direction is the ship turning in
    void shipTurningAnimation(float yaw, float pitch);

    // Function for Bounds Checking
    bool createBoundary(std::vector<InteractableOBJs>&InteractablesList, std::vector<Building>&BuildingsList, Player &somePlayer, Position camPos);
};

#endif
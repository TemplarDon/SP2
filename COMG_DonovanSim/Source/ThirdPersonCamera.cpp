#include "ThirdPersonCamera.h"
#include "Application.h"
#include "Vertex.h"
#include "Mtx44.h"

ThirdPersonCamera::ThirdPersonCamera()
{

}

ThirdPersonCamera::~ThirdPersonCamera()
{

}

void ThirdPersonCamera::Init(const Vector3 position, const Vector3 up, Position *focus, const float camDistance)
{
	Vector3 F(focus->x, focus->y, focus->z);

	camDirection = (F - position).Normalized();

	Vector3 right = camDirection.Cross(up);

	this->camDistance = camDistance;
	this->focus = focus;
	this->position = F - camDirection * camDistance;
	this->target = F;
	this->up = right.Cross(camDirection);
    this->yawingLeft = false;
    this->yawingRight = false;
    this->pitchingDown = false;
    this->pitchingUp = false;

	SetCameraPitchBounds(-30, 15);
	SetCameraDistanceBounds(10, 100);
}

void ThirdPersonCamera::Update(double dt, vector<InteractableOBJs>&InteractablesList, vector<Building>&BuildingsList, Player &somePlayer)
{
	float mouseSpeed = 10;

	if (mouseEnabled)
	{
		float horizontalAngle = mouseSpeed * dt * float(1680 / 2 - Application::mouseX);
		float verticalAngle = mouseSpeed * dt * float(1080 / 2 - Application::mouseY);

		YawCamera(horizontalAngle);
		PitchCamera(verticalAngle);
	}

	shipTurningAnimation(Application::mouseX, Application::mouseY);

	Refocus();
}

void ThirdPersonCamera::SetMouseEnabled(const bool &toggle)
{
	mouseEnabled = toggle;
}

void ThirdPersonCamera::YawCamera(const float degrees)
{
	Mtx44 rotationMatrix;
	rotationMatrix.SetToRotation(degrees, 0, 1, 0);

	camDirection = rotationMatrix * camDirection;
	up = rotationMatrix * up;

	Refocus();
}

void ThirdPersonCamera::PitchCamera(float degrees)
{
	Vector3 right = camDirection.Cross(up);

	float curAngle = GetCameraPitch();

	if (curAngle + degrees > maxPitch) degrees = maxPitch - curAngle;
	if (curAngle + degrees < minPitch) degrees = minPitch - curAngle;

	Mtx44 rotationMatrix;
	rotationMatrix.SetToRotation(degrees, right.x, 0, right.z);

	camDirection = rotationMatrix * camDirection;
	up = rotationMatrix * up;

	Refocus();
}

void ThirdPersonCamera::SetCameraPitchBounds(float min, float max)
{
	this->minPitch = min;
	this->maxPitch = max;
}

void ThirdPersonCamera::Refocus()
{
	Vector3 F(focus->x, focus->y, focus->z);

	this->target = F;
	this->position = F - camDirection * camDistance;
}

float ThirdPersonCamera::GetCameraDistance()
{
	return camDistance;
}

void ThirdPersonCamera::SetCameraDistanceAbsolute(float distance)
{
	camDistance = distance;

	if (camDistance > maxDistance) camDistance = maxDistance;
	if (camDistance < minDistance) camDistance = minDistance;
}

void ThirdPersonCamera::SetCameraDistanceRelative(float distance)
{
	camDistance += distance;

	if (camDistance > maxDistance) camDistance = maxDistance;
	if (camDistance < minDistance) camDistance = minDistance;
}

void ThirdPersonCamera::SetCameraDistanceBounds(float min, float max)
{
	this->minDistance = min;
	this->maxDistance = max;
}

float ThirdPersonCamera::GetCameraPitch()
{
	return Math::RadianToDegree(asin(camDirection.y));
}

Position* ThirdPersonCamera::GetFocusPoint()
{
	return focus;
}

void ThirdPersonCamera::SetFocusPoint(Position *focus)
{
	this->focus = focus;
}

void ThirdPersonCamera::shipTurningAnimation(float yaw, float pitch)
{
    if (pitch > 0 && pitch < 540)
    { 
        pitchingUp = true; 
    }
    else 
    { 
        pitchingUp = false; 
    }

    if (pitch > 540 && pitch < 1080) 
    { 
        pitchingDown = true;
    }
    else 
    { 
        pitchingDown = false; 
    }


    if (yaw > 0 && yaw < 840) 
    { 
        yawingLeft = true; 
    }
    else 
    {
        yawingLeft = false;
    }

    if (yaw > 840 && yaw < 1680) 
    { 
        yawingRight = true;
    }
    else 
    { 
        yawingRight = false; 
    }
    
}
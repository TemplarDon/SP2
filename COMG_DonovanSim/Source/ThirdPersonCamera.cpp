#include "ThirdPersonCamera.h"
#include "Application.h"
#include "Mtx44.h"

ThirdPersonCamera::ThirdPersonCamera()
{

}

ThirdPersonCamera::~ThirdPersonCamera()
{

}

void ThirdPersonCamera::Init(const Vector3 position, const Vector3 up, Vector3 *focus, const float camDistance)
{
	camDirection = (*focus - position).Normalized();

	Vector3 right = camDirection.Cross(up);

	this->camDistance = camDistance;
	this->focus = focus;
	this->position = *(this->focus) - camDirection * camDistance;
	this->target = *(this->focus);
	this->up = right.Cross(camDirection);
}

void ThirdPersonCamera::Update(double dt)
{
	Refocus();
}

void ThirdPersonCamera::YawCamera(const float degrees)
{
	Mtx44 rotationMatrix;
	rotationMatrix.SetToRotation(degrees, 0, 1, 0);

	camDirection = rotationMatrix * camDirection;
	up = rotationMatrix * up;

	Refocus();
}

void ThirdPersonCamera::PitchCamera(const float degrees)
{
	Vector3 right = camDirection.Cross(up);

	Mtx44 rotationMatrix;
	rotationMatrix.SetToRotation(degrees, right.x, 0, right.z);

	camDirection = rotationMatrix * camDirection;
	up = rotationMatrix * up;

	Refocus();
}

void ThirdPersonCamera::Refocus()
{
	this->target = *focus;
	this->position = *focus - camDirection * camDistance;
}

float ThirdPersonCamera::getCameraDistance()
{
	return camDistance;
}

void ThirdPersonCamera::setCameraDistance(float distance)
{
	camDistance = distance;
}

Vector3* ThirdPersonCamera::getFocusPoint()
{
	return focus;
}

void ThirdPersonCamera::setFocusPoint(Vector3 *focus)
{
	this->focus = focus;
}
#include "Camera4.h"
#include "Application.h"
#include "Mtx44.h"

Camera4::Camera4()
{

}

Camera4::~Camera4()
{

}

void Camera4::Init(const Vector3 position, const Vector3 target, const Vector3 up, const float camDistance)
{
	camDirection = (target - position).Normalized();

	Vector3 right = camDirection.Cross(up);

	this->camDistance = camDistance;
	this->position = target - camDirection * camDistance;
	this->target = target;
	this->up = right.Cross(camDirection);
}

void Camera4::Update(double dt, std::vector<Node>&objsMaxMin)
{
	YawCamera(1);
}

void Camera4::YawCamera(float degrees)
{
	Mtx44 rotationMatrix;
	rotationMatrix.SetToRotation(degrees, 0, 1, 0);

	camDirection = rotationMatrix * camDirection;
	up = rotationMatrix * up;
}

void Camera4::pitchCamera(float degrees)
{
	Vector3 right = camDirection.Cross(up);

	Mtx44 rotationMatrix;
	rotationMatrix.SetToRotation(degrees, right.x, 0, right.z);

	camDirection = rotationMatrix * camDirection;
	up = rotationMatrix * up;
}

void Camera4::refocus(Vector3 target)
{
	this->target = target;
	this->position = target - camDirection * camDistance;
}
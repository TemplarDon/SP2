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

    this->canMoveBuilding = true;
    this->canMoveInteractable = true;

	SetCameraPitchBounds(-70, 80);
	SetCameraDistanceBounds(10, 100);
}

void ThirdPersonCamera::Update(double dt, vector<InteractableOBJs>&InteractablesList, vector<Building>&BuildingsList, Player &somePlayer)
{
    float mouseSpeed = 10;
    float horizontalAngle = 0; 
    float verticalAngle = 0; 

    horizontalAngle += mouseSpeed * dt * float(800 / 2 - Application::mouseX);
    verticalAngle += mouseSpeed * dt * float(600 / 2 - Application::mouseY);

    YawCamera(horizontalAngle);
    PitchCamera(verticalAngle);

    cameraMovement(dt, InteractablesList, BuildingsList, somePlayer);

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

void ThirdPersonCamera::cameraMovement(double dt, vector<InteractableOBJs>&InteractablesList, vector<Building>&BuildingsList, Player &somePlayer)
{
    Vector3 view = (target - position).Normalized();
    if (Application::IsKeyPressed('W'))
    {
        view = (target - position).Normalized();
        for (int i = 0; i < InteractablesList.size(); ++i)
        {
            if (InteractablesList[i].canMove == true)
            {
                canMoveInteractable = true;
            }
            else
            {
                canMoveInteractable = false;
                break;
            }
        }

        for (int i = 0; i < BuildingsList.size(); ++i)
        {
            if (BuildingsList[i].canMove == true)
            {
                canMoveBuilding = true;
            }
            else
            {
                canMoveBuilding = false;
                break;
            }
        }

        if (canMoveBuilding == true && canMoveInteractable == true)
        {
            position = position + view;
            target = target + view;

            somePlayer.pos.x += position.x;
            somePlayer.pos.y += position.y;
            somePlayer.pos.z += position.x;

            focus->x += view.x;
            focus->y += view.y;
            focus->z += view.z;
        }

    }

    if (Application::IsKeyPressed('S'))
    {
        view = (target - position).Normalized();
        int offSetCount = 0;
        for (int i = 0; i < InteractablesList.size(); ++i)
        {
            if (InteractablesList[i].canMove == true)
            {
                canMoveInteractable = true;
            }
            else
            {
                canMoveInteractable = false;
                break;
            }
        }

        for (int i = 0; i < BuildingsList.size(); ++i)
        {
            if (BuildingsList[i].canMove == true)
            {
                canMoveBuilding = true;
            }
            else
            {
                canMoveBuilding = false;
                break;
            }
        }

        if (canMoveBuilding == true && canMoveInteractable == true)
        {
            position = position - view;
            target = target +- view;

            somePlayer.pos.x -= position.x;
            somePlayer.pos.y -= position.y;
            somePlayer.pos.z -= position.x;

            focus->x -= view.x;
            focus->y -= view.y;
            focus->z -= view.z;
        }
    }

    if (Application::IsKeyPressed('D'))
    {
        Vector3 right = view.Cross(up);
        right.Normalize();
        view = (target - position).Normalized();
        int offSetCount = 0;
        for (int i = 0; i < InteractablesList.size(); ++i)
        {
            if (InteractablesList[i].canMove == true)
            {
                canMoveInteractable = true;
            }
            else
            {
                canMoveInteractable = false;
                break;
            }
        }

        for (int i = 0; i < BuildingsList.size(); ++i)
        {
            if (BuildingsList[i].canMove == true)
            {
                canMoveBuilding = true;
            }
            else
            {
                canMoveBuilding = false;
                break;
            }
        }

        if (canMoveBuilding == true && canMoveInteractable == true)
        {
            position += right.Normalized();
            target += right.Normalized();

            somePlayer.pos.x += right.Normalized().x;
            somePlayer.pos.z += right.Normalized().z;

            focus->x += right.Normalized().x;
            focus->z += right.Normalized().z;
        }
    }

    if (Application::IsKeyPressed('A'))
    {
        Vector3 right = view.Cross(up);
        right.Normalize();
        view = (target - position).Normalized();
        int offSetCount = 0;
        for (int i = 0; i < InteractablesList.size(); ++i)
        {
            if (InteractablesList[i].canMove == true)
            {
                canMoveInteractable = true;
            }
            else
            {
                canMoveInteractable = false;
                break;
            }
        }

        for (int i = 0; i < BuildingsList.size(); ++i)
        {
            if (BuildingsList[i].canMove == true)
            {
                canMoveBuilding = true;
            }
            else
            {
                canMoveBuilding = false;
                break;
            }
        }

        if (canMoveBuilding == true && canMoveInteractable == true)
        {
            position -= right.Normalized();
            target -= right.Normalized();

            somePlayer.pos.x -= right.Normalized().x;
            somePlayer.pos.z -= right.Normalized().z;

            focus->x -= right.Normalized().x;
            focus->z -= right.Normalized().z;
        }
    }
}

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
    this->defaultRightVec = right;
    this->defaultUpVec = up;

	SetCameraPitchBounds(-30, 15);
	SetCameraYawBounds(30, -30);
	SetCameraDistanceBounds(10, 100);
}

void ThirdPersonCamera::Update(double dt, vector<InteractableOBJs>&InteractablesList, vector<Building>&BuildingsList, Player &somePlayer)
{
	float mouseSpeed = 10;

	if (mouseEnabled)
	{
		float horizontalAngle = mouseSpeed * dt * float(1680 / 2 - Application::mouseX);
		float verticalAngle = mouseSpeed * dt * float(1080 / 2 - Application::mouseY);

		RotateYawBoundsDirection(float(dt) * 60);

		YawCamera(horizontalAngle);
		PitchCamera(verticalAngle);

        shipTurningAnimation(Application::mouseX, Application::mouseY);
	}

	Refocus();
}

void ThirdPersonCamera::SetMouseEnabled(const bool &toggle)
{
	mouseEnabled = toggle;
}

void ThirdPersonCamera::YawCamera(float degrees)
{
	Mtx44 rotationMatrix;

	Vector3 C = camDirection;
	C.y = 0;
	C.Normalize();

	bool isDifferencePositive = yawBoundsDirection.Cross(C).y >= 0;
	float angleOffset = Math::RadianToDegree(acos(yawBoundsDirection.Dot(C)));

	Vector3 LB, RB;

	rotationMatrix.SetToRotation(yawBoundsRange, 0, 1, 0);
	LB = rotationMatrix * yawBoundsDirection;
	rotationMatrix.SetToRotation(-yawBoundsRange, 0, 1, 0);
	RB = rotationMatrix * yawBoundsDirection;

	float A;

	if (degrees >= 0)
	{
		A = angleOffset * (isDifferencePositive ? 1.0f : -1.0f);
		if (A + degrees > yawBoundsRange) degrees = yawBoundsRange - A;
		if (A + degrees < -yawBoundsRange) degrees = -yawBoundsRange - A;
	}
	else
	{
		A = angleOffset * (isDifferencePositive ? -1.0f : 1.0f);
		if (A - degrees > yawBoundsRange) degrees = A - yawBoundsRange;
		if (A - degrees < -yawBoundsRange) degrees = A + yawBoundsRange;
	}

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

//Taking in a vector direction on the xz plane and bounding angle.
void ThirdPersonCamera::SetCameraYawBounds(Vector3 direction, float range)
{
	direction.y = 0;

	yawBoundsDirection = direction.Normalized();

	yawBoundsRange = range;
}

//Taking in left and right bounds in degrees (CCW-based).
void ThirdPersonCamera::SetCameraYawBounds(float boundsLeft, float boundsRight)
{
	if (boundsLeft < boundsRight) boundsLeft += 360;
	Mtx44 rotationMatrix;
	rotationMatrix.SetToRotation((boundsLeft + boundsRight) / 2, 0, 1, 0);

	yawBoundsDirection = rotationMatrix * Vector3(1, 0, 0);

	yawBoundsRange = boundsLeft / 2 - boundsRight / 2;
}

//Rotates CCW the direction for Yaw bounding along the y-axis.
void ThirdPersonCamera::RotateYawBoundsDirection(float degrees)
{
	Mtx44 rotationMatrix;
	rotationMatrix.SetToRotation(degrees, 0, 1, 0);

	yawBoundsDirection = rotationMatrix * yawBoundsDirection;
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

/*void ThirdPersonCamera::cameraMovement(double dt, vector<InteractableOBJs>&InteractablesList, vector<Building>&BuildingsList, Player &somePlayer)
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
            position += view;
            target += view;

            somePlayer.pos.x += view.x;
            somePlayer.pos.y += view.y;
            somePlayer.pos.z += view.x;

            focus->x += view.x;
            focus->y += view.y;
            focus->z += view.z;
            shipTurningAnimation(Application::mouseX, Application::mouseY);
            
        }

        

    }

    //if (Application::IsKeyPressed('S'))
    //{
    //    view = (target - position).Normalized();
    //    int offSetCount = 0;
    //    for (int i = 0; i < InteractablesList.size(); ++i)
    //    {
    //        if (InteractablesList[i].canMove == true)
    //        {
    //            canMoveInteractable = true;
    //        }
    //        else
    //        {
    //            canMoveInteractable = false;
    //            break;
    //        }
    //    }

    //    for (int i = 0; i < BuildingsList.size(); ++i)
    //    {
    //        if (BuildingsList[i].canMove == true)
    //        {
    //            canMoveBuilding = true;
    //        }
    //        else
    //        {
    //            canMoveBuilding = false;
    //            break;
    //        }
    //    }

    //    if (canMoveBuilding == true && canMoveInteractable == true)
    //    {
    //        position = position - view;
    //        target = target - view;

    //        somePlayer.pos.x -= view.x;
    //        somePlayer.pos.y -= view.y;
    //        somePlayer.pos.z -= view.x;

    //        focus->x -= view.x;
    //        focus->y -= view.y;
    //        focus->z -= view.z;
    //    }
    //}

    //if (Application::IsKeyPressed('D'))
    //{
    //    Vector3 right = view.Cross(up);
    //    right.Normalize();
    //    view = (target - position).Normalized();
    //    int offSetCount = 0;
    //    for (int i = 0; i < InteractablesList.size(); ++i)
    //    {
    //        if (InteractablesList[i].canMove == true)
    //        {
    //            canMoveInteractable = true;
    //        }
    //        else
    //        {
    //            canMoveInteractable = false;
    //            break;
    //        }
    //    }

    //    for (int i = 0; i < BuildingsList.size(); ++i)
    //    {
    //        if (BuildingsList[i].canMove == true)
    //        {
    //            canMoveBuilding = true;
    //        }
    //        else
    //        {
    //            canMoveBuilding = false;
    //            break;
    //        }
    //    }

    //    if (canMoveBuilding == true && canMoveInteractable == true)
    //    {
    //        position += right.Normalized();
    //        target += right.Normalized();

    //        somePlayer.pos.x += right.Normalized().x;
    //        somePlayer.pos.z += right.Normalized().z;

    //        focus->x += right.Normalized().x;
    //        focus->z += right.Normalized().z;
    //    }
    //}

    //if (Application::IsKeyPressed('A'))
    //{
    //    Vector3 right = view.Cross(up);
    //    right.Normalize();
    //    view = (target - position).Normalized();
    //    int offSetCount = 0;
    //    for (int i = 0; i < InteractablesList.size(); ++i)
    //    {
    //        if (InteractablesList[i].canMove == true)
    //        {
    //            canMoveInteractable = true;
    //        }
    //        else
    //        {
    //            canMoveInteractable = false;
    //            break;
    //        }
    //    }

    //    for (int i = 0; i < BuildingsList.size(); ++i)
    //    {
    //        if (BuildingsList[i].canMove == true)
    //        {
    //            canMoveBuilding = true;
    //        }
    //        else
    //        {
    //            canMoveBuilding = false;
    //            break;
    //        }
    //    }

    //    if (canMoveBuilding == true && canMoveInteractable == true)
    //    {
    //        position -= right.Normalized();
    //        target -= right.Normalized();

    //        somePlayer.pos.x -= right.Normalized().x;
    //        somePlayer.pos.z -= right.Normalized().z;

    //        focus->x -= right.Normalized().x;
    //        focus->z -= right.Normalized().z;
    //    }
    //}
}
*/

void ThirdPersonCamera::shipTurningAnimation(float yaw, float pitch)
{
    if (pitch > 0 && pitch < 540) { pitchingUp = true; }
    else { pitchingUp = false; }

    if (pitch > 540 && pitch < 1080) { pitchingDown = true; }
    else { pitchingDown = false; }

    if (yaw > 0 && yaw < 840) { yawingLeft = true; }
    else { yawingLeft = false; }

    if (yaw > 840 && yaw < 1680) { yawingRight = true; }
    else { yawingRight = false; }
}
#include "FirstPersonCamera.h"
#include "Application.h"
#include "Mtx44.h"

FirstPersonCamera::FirstPersonCamera()
{
}

FirstPersonCamera::~FirstPersonCamera()
{
}

void FirstPersonCamera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
    canMoveBuilding = true;
    canMoveInteractable = true;
}

void FirstPersonCamera::Update(double dt, vector<InteractableOBJs>&InteractablesList, vector<Building>&BuildingsList, Player &somePlayer)
{
	Vector3 boundary(1000, 1000, 1000);

	speed = 30;
	mouseSpeed = 12;

	static const float CAMERA_SPEED = 50.f;
	if (Application::IsKeyPressed('R'))
	{
		Reset();
	}

	//view.y < 0.9396 && view.y > -09396

	//Mouse - Bugged
	//int Angle = 50;
	//horizontalAngle += mouseSpeed * dt * float(1680 / 2 - Application::mouseX);
	//if (verticalAngle + mouseSpeed * dt * float(1080 / 2 - Application::mouseY) < Angle && verticalAngle + mouseSpeed * dt * float(1080 / 2 - Application::mouseY) > -Angle)
	//{
	//    verticalAngle += mouseSpeed * dt * float(1080 / 2 - Application::mouseY);
	//}

	//Vector3 view(cos(Math::DegreeToRadian(verticalAngle)) * sin(Math::DegreeToRadian(horizontalAngle)),
	//	         sin(Math::DegreeToRadian(verticalAngle)),
	//	        cos(Math::DegreeToRadian(verticalAngle)) * cos(Math::DegreeToRadian(horizontalAngle)));


	//Vector3 Right(sin(Math::DegreeToRadian(horizontalAngle-90)), 0, cos(Math::DegreeToRadian(horizontalAngle-90)));

	//up = Right.Cross(view);

 //   target = position + view.Normalized();


    // Mouse - DonoDon
    Vector3 view = (target - position).Normalized();

    float yaw = 0;
    float pitch = 0;

    yaw = (float)(mouseSpeed  * dt * (1680 / 2 - Application::mouseX));

    pitch = (float)(mouseSpeed * dt * (1080 / 2 - Application::mouseY));

    // Mouse
    Mtx44 rotationYaw;
    rotationYaw.SetToRotation(yaw, 0, 1, 0);
    view = (target - position);
    Vector3 right = view.Cross(up);
    view = rotationYaw * view;

    target = view + position;
    up = rotationYaw * up;

    Mtx44 rotationPitch;
    view = (target - position);
    right = view.Cross(up);
    right.y = 0;
    up = right.Cross(view).Normalized();
    rotationPitch.SetToRotation(pitch, right.x, right.y, right.z);

    view = rotationPitch * view;
    target = view + position;

    view = (target - position).Normalized();
    Position camPos; // Position to check collision with

    if (Application::IsKeyPressed('W'))
    {
        camPos.Set(position.x + view.x, position.Normalized().y + view.y, position.z + view.z);
        if (createBoundary(InteractablesList, BuildingsList, somePlayer, camPos))
        {
            position.x = position.x + view.x; // position = position + view
            position.z = position.z + view.z; // position = position + view
            target.x = target.x + view.x; // target = target + view
            target.z = target.z + view.z; // target = target + view

            somePlayer.pos.x += view.x;
            somePlayer.pos.z += view.z;
        }
    }

    if (Application::IsKeyPressed('S'))
    {
        camPos.Set(position.x - view.x, position.Normalized().y - view.y, position.z - view.z);
        if (createBoundary(InteractablesList, BuildingsList, somePlayer, camPos))
        {
            position.x = position.x - (target - position).Normalized().x; 
            position.z = position.z - (target - position).Normalized().z; 
            target.x = target.x - (target - position).Normalized().x; 
            target.z = target.z - (target - position).Normalized().z; 

            somePlayer.pos.x -= view.x;
            somePlayer.pos.z -= view.z;
        }
    }

    if (Application::IsKeyPressed('A'))
    {
        camPos.Set(position.x - right.Normalized().x, position.Normalized().y - right.Normalized().y, position.z - right.Normalized().z);
        if (createBoundary(InteractablesList, BuildingsList, somePlayer, camPos))
        {
            position -= right.Normalized();
            target -= right.Normalized();

            somePlayer.pos.x -= right.Normalized().x;
            somePlayer.pos.z -= right.Normalized().z;
        }
    }

    if (Application::IsKeyPressed('D'))
    {
        camPos.Set(position.x + right.Normalized().x, position.Normalized().y + right.Normalized().y, position.z + right.Normalized().z);
        if (createBoundary(InteractablesList, BuildingsList, somePlayer, camPos))
        {
            position += right.Normalized();
            target += right.Normalized();

            somePlayer.pos.x += right.Normalized().x;
            somePlayer.pos.z += right.Normalized().z;
        }
    }

}

bool FirstPersonCamera::createBoundary(std::vector<InteractableOBJs>&InteractablesList, std::vector<Building>&BuildingsList, Player &somePlayer, Position camPos)
{
    Position maxPos;
    Position minPos;

    for (int i = 0; i < InteractablesList.size(); ++i)
    {
        maxPos.x = InteractablesList[i].maxPos.x;
        maxPos.y = InteractablesList[i].maxPos.y;
        maxPos.z = InteractablesList[i].maxPos.z;

        minPos.x = InteractablesList[i].minPos.x;
        minPos.y = InteractablesList[i].minPos.y;
        minPos.z = InteractablesList[i].minPos.z;

        // Scaling
        maxPos.x = maxPos.x * InteractablesList[i].scaleOffSet;
        maxPos.y = maxPos.y * InteractablesList[i].scaleOffSet;
        maxPos.z = maxPos.z * InteractablesList[i].scaleOffSet;

        minPos.x = minPos.x * InteractablesList[i].scaleOffSet;
        minPos.y = minPos.y * InteractablesList[i].scaleOffSet;
        minPos.z = minPos.z * InteractablesList[i].scaleOffSet;

        // Rotation
        Mtx44 rotation;
        Vector3 tempMax;
        Vector3 tempMin;

        tempMax.x = maxPos.x;
        tempMax.y = maxPos.y;
        tempMax.z = maxPos.z;

        tempMin.x = minPos.x;
        tempMin.y = minPos.y;
        tempMin.z = minPos.z;
        if (InteractablesList[i].rotateAxis.x == 1)
        {
            rotation.SetToRotation(InteractablesList[i].rotateAngle, 1, 0, 0);
            tempMax = rotation * tempMax;
            tempMin = rotation * tempMin;
        }
        if (InteractablesList[i].rotateAxis.y == 1)
        {
            rotation.SetToRotation(InteractablesList[i].rotateAngle, 0, 1, 0);
            tempMax = rotation * tempMax;
            tempMin = rotation * tempMin;
        }
        if (InteractablesList[i].rotateAxis.z == 1)
        {
            rotation.SetToRotation(InteractablesList[i].rotateAngle, 0, 0, 1);
            tempMax = rotation * tempMax;
            tempMin = rotation * tempMin;
        }

        maxPos.x = tempMax.x;
        maxPos.y = tempMax.y;
        maxPos.z = tempMax.z;

        minPos.x = tempMin.x;
        minPos.y = tempMin.y;
        minPos.z = tempMin.z;

        // Translating
        maxPos.x += InteractablesList[i].pos.x;
        maxPos.y += InteractablesList[i].pos.y;
        maxPos.z += InteractablesList[i].pos.z;

        minPos.x += InteractablesList[i].pos.x;
        minPos.y += InteractablesList[i].pos.y;
        minPos.z += InteractablesList[i].pos.z;

        if ((camPos.x > maxPos.x || camPos.x < minPos.x) || (camPos.y > maxPos.y || camPos.y < minPos.y) || (camPos.z > maxPos.z || camPos.z < minPos.z))
        {
            InteractablesList[i].canMove = true;
        }
        else
        {
            InteractablesList[i].canMove = false;
        }
    }


    for (int i = 0; i < BuildingsList.size(); ++i)
    {
        maxPos.x = BuildingsList[i].maxPos.x;
        maxPos.y = BuildingsList[i].maxPos.y;
        maxPos.z = BuildingsList[i].maxPos.z;

        minPos.x = BuildingsList[i].minPos.x;
        minPos.y = BuildingsList[i].minPos.y;
        minPos.z = BuildingsList[i].minPos.z;

        // Scaling
        maxPos.x = maxPos.x * BuildingsList[i].scaleOffSet;
        maxPos.y = maxPos.y * BuildingsList[i].scaleOffSet;
        maxPos.z = maxPos.z * BuildingsList[i].scaleOffSet;

        minPos.x = minPos.x * BuildingsList[i].scaleOffSet;
        minPos.y = minPos.y * BuildingsList[i].scaleOffSet;
        minPos.z = minPos.z * BuildingsList[i].scaleOffSet;

        // Translating
        maxPos.x += BuildingsList[i].pos.x;
        maxPos.y += BuildingsList[i].pos.y;
        maxPos.z += BuildingsList[i].pos.z;

        minPos.x += BuildingsList[i].pos.x;
        minPos.y += BuildingsList[i].pos.y;
        minPos.z += BuildingsList[i].pos.z;

        if ((camPos.x > maxPos.x || camPos.x < minPos.x) || (camPos.y > maxPos.y || camPos.y < minPos.y) || (camPos.z > maxPos.z || camPos.z < minPos.z))
        {
            BuildingsList[i].canMove = true;
        }
        else
        {
            BuildingsList[i].canMove = false;
        }

    }

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
        return true;
    }
    else
    {
        return false;
    }
}

void FirstPersonCamera::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}
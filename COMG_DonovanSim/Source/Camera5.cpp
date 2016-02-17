#include "Camera5.h"
#include "Application.h"
#include "Mtx44.h"

Camera5::Camera5()
{
}

Camera5::~Camera5()
{
}

void Camera5::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
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

void Camera5::Update(double dt, vector<InteractableOBJs>&InteractablesList, vector<Building>&BuildingsList, Player &somePlayer)
{
	Vector3 boundary(1000, 1000, 1000);

	speed = 30;
	mouseSpeed = 10;

	static const float CAMERA_SPEED = 50.f;
	if (Application::IsKeyPressed('R'))
	{
		Reset();
	}

	//view.y < 0.9396 && view.y > -09396

	//Mouse
	/*int Angle = 50;
	horizontalAngle += mouseSpeed * dt * float(800 / 2 - Application::mouseX);
	if (verticalAngle + mouseSpeed * dt * float(600 / 2 - Application::mouseY) < Angle && verticalAngle + mouseSpeed * dt * float(600 / 2 - Application::mouseY) > -Angle)
	{
		verticalAngle += mouseSpeed * dt * float(600 / 2 - Application::mouseY);
	}

	Vector3 Direction(cos(Math::DegreeToRadian(verticalAngle)) * sin(Math::DegreeToRadian(horizontalAngle)),
		sin(Math::DegreeToRadian(verticalAngle)),
		cos(Math::DegreeToRadian(verticalAngle)) * cos(Math::DegreeToRadian(horizontalAngle)));


	Vector3 Right(sin(Math::DegreeToRadian(horizontalAngle) - 3.14f / 2.0f), 0, cos(Math::DegreeToRadian(horizontalAngle) - 3.14 / 2.9f));

	up = Right.Cross(Direction);*/

    Vector3 view = (target - position).Normalized();
	if (Application::IsKeyPressed('W'))
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
            position.x = position.x + view.x; // position = position + view
            position.z = position.z + view.z; // position = position + view
            target.x = target.x + view.x; // target = target + view
            target.z = target.z + view.z; // target = target + view

            somePlayer.pos.x += position.x;
            somePlayer.pos.z += position.x;
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
            position.x = position.x - (target - position).Normalized().x; 
            position.z = position.z - (target - position).Normalized().z; 
            target.x = target.x - (target - position).Normalized().x; 
            target.z = target.z - (target - position).Normalized().z; 

            somePlayer.pos.x -= position.x;
            somePlayer.pos.z -= position.x;
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
        }
	}

    
	//target = position + Direction;

}

void Camera5::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}
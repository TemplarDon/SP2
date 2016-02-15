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
}

void Camera5::Update(double dt)
{
	Vector3 boundary(1000, 1000, 1000);
	/*Vector3 boundary = (-50, -50, -50);*/

	static const float CAMERA_SPEED = 50.f;
	if (Application::IsKeyPressed('R'))
	{
		Reset();
	}

	//view.y < 0.9396 && view.y > -09396

	//Mouse
	int Angle = 50;
	horizontalAngle += mouseSpeed * dt * float(800 / 2 - Application::mouseX);
	if (verticalAngle + mouseSpeed * dt * float(600 / 2 - Application::mouseY) < Angle && verticalAngle + mouseSpeed * dt * float(600 / 2 - Application::mouseY) > -Angle)
	{
		verticalAngle += mouseSpeed * dt * float(600 / 2 - Application::mouseY);
	}

	Vector3 Direction(cos(Math::DegreeToRadian(verticalAngle)) * sin(Math::DegreeToRadian(horizontalAngle)),
		sin(Math::DegreeToRadian(verticalAngle)),
		cos(Math::DegreeToRadian(verticalAngle)) * cos(Math::DegreeToRadian(horizontalAngle)));


	Vector3 Right(sin(Math::DegreeToRadian(horizontalAngle) - 3.14f / 2.0f), 0, cos(Math::DegreeToRadian(horizontalAngle) - 3.14 / 2.9f));

	up = Right.Cross(Direction);


	if (Application::IsKeyPressed('W'))
	{
		if (position.x + Direction.x * dt * speed < boundary.x && position.x + Direction.x * dt * speed > -boundary.x)
		{
			position.x += Direction.x * dt * speed;
		}

		//position.y += Direction.y * dt * speed;

		if (position.z + Direction.z * dt * speed < boundary.z && position.z + Direction.z * dt * speed > -boundary.z)
		{
			position.z += Direction.z * dt * speed;
		}

	}

	if (Application::IsKeyPressed('S'))
	{
		if (position.x - Direction.x * dt * speed < boundary.x && position.x - Direction.x * dt * speed > -boundary.x)
		{
			position.x -= Direction.x * dt * speed;
		}

		//position.y -= Direction.y * dt * speed;

		if (position.z - Direction.z * dt * speed < boundary.z && position.z - Direction.z * dt * speed > -boundary.z)
		{
			position.z -= Direction.z * dt * speed;
		}
	}

	if (Application::IsKeyPressed('D'))
	{
		if (position.x + Right.x * dt * speed < boundary.x && position.x + Right.x * dt * speed > -boundary.x)
		{
			position.x += Right.x * dt * speed;
		}


		//position += Right * dt * speed;

		if (position.z + Direction.z * dt * speed < boundary.z && position.z + Direction.z * dt * speed > -boundary.z)
		{
			position.z += Right.z * dt * speed;

		}
	}

	if (Application::IsKeyPressed('A'))
	{
		if (position.x - Direction.x * dt * speed < boundary.x && position.x - Direction.x * dt * speed > -boundary.x)
		{
			position.x -= Right.x * dt * speed;
		}
		//position -= Right * dt * speed;

		if (position.z - Direction.z * dt * speed < boundary.z && position.z - Direction.z * dt * speed > -boundary.z)
		{
			position.z -= Right.z * dt * speed;
		}
	}

	target = position + Direction;

}

void Camera5::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}
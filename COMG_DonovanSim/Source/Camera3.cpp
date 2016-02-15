#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"
#include "Asn2.h"

Camera3::Camera3()
{
}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
    this->position = defaultPosition = pos;
    this->target = defaultTarget = target;
    Vector3 view = (target - position).Normalized();
    Vector3 right = view.Cross(up);
    right.y = 0;
    right.Normalize();
    this->up = defaultUp = right.Cross(view).Normalized();
    canMove = true;
}

void Camera3::Update(double dt, std::vector<Node>&objsMaxMin)
{
    static const float CAMERA_SPEED = 5.f;

    bool canMove = false;
    Vector3 view = (target - position).Normalized();

    //float offSetDist = 4.0f;
    //Position cameraPos;
    //cameraPos.x = position.x + view.x;
    //cameraPos.y = position.y + view.y;
    //cameraPos.z = position.z + view.z;

    Position cameraPos;
    Position maxPos;
    Position minPos;


    if (Application::IsKeyPressed('W')) // Move Forward
    {

        view = (target - position).Normalized();
        int offSetCount = 0;
        for (int i = 0; i < objsMaxMin.size(); ++i)
        {
            if (objsMaxMin[i].canMove == true)
            {
                canMove = true;
            }
            else
            {
                canMove = true;
                break;
            }
        }

        if (canMove == true)
        {
            position.x = position.x + view.x; // position = position + view
            position.z = position.z + view.z; // position = position + view
            target.x = target.x + view.x; // target = target + view
            target.z = target.z + view.z; // target = target + view
        }

    }

    if (Application::IsKeyPressed('A')) // Strafe Left
    {
        Vector3 view = (target - position).Normalized();
        Vector3 right = view.Cross(up);
        right.Normalize();

        for (int i = 0; i < objsMaxMin.size(); ++i)
        {
            if (objsMaxMin[i].canMove == true)
            {
                canMove = true;
            }
            else
            {
                canMove = true;
                break;
            }
        }

        if (canMove == true)
        {
            position -= right.Normalized();
            target -= right.Normalized();
        }
       
        

    }

    if (Application::IsKeyPressed('D')) // Strafe Right
    {
        int offSetCount = 0;
        Vector3 view = (target - position).Normalized();
        Vector3 right = view.Cross(up);
        right.Normalize();
        
        for (int i = 0; i < objsMaxMin.size(); ++i)
        {
            if (objsMaxMin[i].canMove == true)
            {
                canMove = true;
            }
            else
            {
                canMove = true;
                break;
            }
        }

        if (canMove == true)
        {
            position += right.Normalized();
            target += right.Normalized();
        }
        

    }

    if (Application::IsKeyPressed('S')) // Move Backwards
    {

        for (int i = 0; i < objsMaxMin.size(); ++i)
        {
            cameraPos.x = position.x - view.x;
            cameraPos.y = position.y - view.y;
            cameraPos.z = position.z - view.z;

            // Scaling
            maxPos.x = objsMaxMin[i].maxPos.x * objsMaxMin[i].scaleOffSet;
            maxPos.y = objsMaxMin[i].maxPos.y * objsMaxMin[i].scaleOffSet;
            maxPos.z = objsMaxMin[i].maxPos.z * objsMaxMin[i].scaleOffSet;

            minPos.x = objsMaxMin[i].minPos.x * objsMaxMin[i].scaleOffSet;
            minPos.y = objsMaxMin[i].minPos.y * objsMaxMin[i].scaleOffSet;
            minPos.z = objsMaxMin[i].minPos.z * objsMaxMin[i].scaleOffSet;

            // Rotation
            Mtx44 rotation;
            Vector3 tempMax;
            Vector3 tempMin;

            tempMax.x = objsMaxMin[i].maxPos.x;
            tempMax.y = objsMaxMin[i].maxPos.y;
            tempMax.z = objsMaxMin[i].maxPos.z;

            tempMin.x = objsMaxMin[i].minPos.x;
            tempMin.y = objsMaxMin[i].minPos.y;
            tempMin.z = objsMaxMin[i].minPos.z;
            if (objsMaxMin[i].rotateAxis.x == 1)
            {
                rotation.SetToRotation(objsMaxMin[i].rotateAngle, 1, 0, 0);
                tempMax = rotation * tempMax;
                tempMin = rotation * tempMin;
            }
            if (objsMaxMin[i].rotateAxis.y == 1)
            {
                rotation.SetToRotation(objsMaxMin[i].rotateAngle, 0, 1, 0);
                tempMax = rotation * tempMax;
                tempMin = rotation * tempMin;
            }
            if (objsMaxMin[i].rotateAxis.z == 1)
            {
                rotation.SetToRotation(objsMaxMin[i].rotateAngle, 0, 0, 1);
                tempMax = rotation * tempMax;
                tempMin = rotation * tempMin;
            }

            objsMaxMin[i].maxPos.x = tempMax.x;
            objsMaxMin[i].maxPos.y = tempMax.y;
            objsMaxMin[i].maxPos.z = tempMax.z;

            objsMaxMin[i].minPos.x = tempMin.x;
            objsMaxMin[i].minPos.y = tempMin.y;
            objsMaxMin[i].minPos.z = tempMin.z;

            // Translating
            maxPos.x += objsMaxMin[i].offSet.x;
            maxPos.y += objsMaxMin[i].offSet.y;
            maxPos.z += objsMaxMin[i].offSet.z;

            minPos.x += objsMaxMin[i].offSet.x;
            minPos.y += objsMaxMin[i].offSet.y;
            minPos.z += objsMaxMin[i].offSet.z;

            if ((cameraPos.x > maxPos.x || cameraPos.x < minPos.x) || (cameraPos.z > maxPos.z || cameraPos.z < minPos.z))
            {
                canMove = true;
            }
            else
            {
                canMove = true;
                break;
            }
        }


        if (canMove == true)
        {
            position.x = position.x - (target - position).Normalized().x; // position = position + view
            position.z = position.z - (target - position).Normalized().z; // position = position + view
            target.x = target.x - (target - position).Normalized().x; // position = position + view
            target.z = target.z - (target - position).Normalized().z; // position = position + view
        }
        

    }

    // -------------------------------------- Mouse Controls ------------------------------------------------------------- //
    mouseSensitivty = 2;
    float yaw = 0;
    float pitch = 0;

    yaw = (float)(mouseSensitivty * CAMERA_SPEED * dt * (800 / 2 - Application::mouseX));

    pitch = (float)(mouseSensitivty * CAMERA_SPEED * dt * (600 / 2 - Application::mouseY));
    


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
    

    

    

    // -------------------------------------- Mouse Controls ------------------------------------------------------------- //

    if (Application::IsKeyPressed(VK_SHIFT)) // Move Down
    {
        position.y += (float)(CAMERA_SPEED * dt * -1.f);
        target.y += (float)(CAMERA_SPEED * dt * -1.f);
    }
    if (Application::IsKeyPressed(VK_SPACE)) // Move Up
    {
		if (position.y < 10)
		{
			for (int i = 0; i < 10; i++)
			{
				position.y += (float)(i * dt);
				target.y += (float)(i * dt);
			}
			if (position.y >= 10)
			{
				for (int i = 0; i < 10; i++)
				{
					position.y -= (float)(i * dt);
					target.y -= (float)(i * dt);
				}
			}
		}
    }

    if (Application::IsKeyPressed('R'))
    {
        Reset();
    }
    


    //if (Application::IsKeyPressed('Q')) // Turn Left
    //{
    //    float yaw = (float)(CAMERA_SPEED * dt);
    //    Mtx44 rotation;
    //    rotation.SetToRotation(yaw, 0, 1, 0);
    //    Vector3 view = (target - position);
    //    Vector3 right = view.Cross(up);

    //    //-------------------------- ATTEMPTED FORMULA --------------------------------------
    //    //vecRotation.z = sin(yaw) * view.Length();
    //    //vecRotation.x = vecRotation.z / tan((180 - yaw) /2);

    //    //target.x += vecRotation.x;
    //    //target.z += vecRotation.z;
    //    //-------------------------- ATTEMPTED FORMULA --------------------------------------

    //    view = rotation * view;
    //    target = view + position;
    //    up = rotation * up;
    //}

    //if (Application::IsKeyPressed('E')) // Turn Right
    //{
    //    float yaw = (float)(CAMERA_SPEED * dt * -1.f);
    //    Mtx44 rotation;
    //    rotation.SetToRotation(yaw, 0, 1, 0);
    //    Vector3 view = (target - position);

    //    view = rotation * view;
    //    target = view + position;
    //    up = rotation * up;
    //}

    //if (Application::IsKeyPressed('Z')) // Look Up
    //{
    //    float pitch = (float)(CAMERA_SPEED * dt);
    //    Mtx44 rotation;
    //    Vector3 view = (target - position);
    //    Vector3 right = view.Cross(up);
    //    right.y = 0;
    //    up = right.Cross(view).Normalized();
    //    rotation.SetToRotation(pitch, right.x, right.y, right.z);

    //    view = rotation * view;
    //    target = view + position;
    //}

    //if (Application::IsKeyPressed('X')) // Look Down
    //{
    //    float pitch = (float)(CAMERA_SPEED * dt * -1.f);
    //    Mtx44 rotation;
    //    Vector3 view = (target - position);
    //    Vector3 right = view.Cross(up);
    //    right.y = 0;
    //    up = right.Cross(view).Normalized();
    //    rotation.SetToRotation(pitch, right.x, right.y, right.z);

    //    view = rotation * view;
    //    target = view + position;
    //}


}

void Camera3::Reset()
{
    position = defaultPosition;
    target = defaultTarget;
    up = defaultUp;
}
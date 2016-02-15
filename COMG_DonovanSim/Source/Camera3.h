#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "Camera.h"

#include "MyMath.h"
#include "vertex.h"
#include "Node.h"
#include "Mesh.h"

class Camera3 : public Camera
{
public:
    Vector3 defaultPosition;
    Vector3 defaultTarget;
    Vector3 defaultUp;
    Vector3 vecRotation;

    float mouseSensitivty;
    bool canMove;

    Camera3();
    ~Camera3();
    virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
    virtual void Update(double dt, std::vector<Node>&objsMaxMin);
    virtual void Reset();
};

#endif
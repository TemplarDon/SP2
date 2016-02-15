#ifndef CAMERA_4_H
#define CAMERA_4_H

#include "Camera.h"

#include "MyMath.h"
#include "vertex.h"
#include "Node.h"
#include "Mesh.h"

//Camera4: Third-person camera
class Camera4 : public Camera
{
private:
	float camDistance;
	float mouseSensitivty;

	Vector3 camDirection;

public:
	Camera4();
	~Camera4();
	virtual void Init(const Vector3 position, const Vector3 target, const Vector3 up, const float camDistance);
	virtual void Update(double dt, std::vector<Node>&objsMaxMin);

	void YawCamera(const float degrees);
	void pitchCamera(const float degrees);
	void refocus(Vector3 position);
};

#endif
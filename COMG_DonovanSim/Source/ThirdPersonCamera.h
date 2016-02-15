#ifndef _THIRDPERSONCAMERA_H_
#define _THIRDPERSONCAMERA_H_

#include "Camera.h"

#include "MyMath.h"

class ThirdPersonCamera : public Camera
{
private:
	float camDistance;
	Vector3 *focus;

public:
	Vector3 camDirection;

	ThirdPersonCamera();
	~ThirdPersonCamera();
	virtual void Init(const Vector3 position, const Vector3 up, Vector3 *focus, const float camDistance);
	virtual void Update(double dt);

	void YawCamera(const float degrees);
	void PitchCamera(const float degrees);
	void Refocus();

	float getCameraDistance();
	void setCameraDistance(float distance);

	Vector3* getFocusPoint();
	void setFocusPoint(Vector3 *focus);
};

#endif
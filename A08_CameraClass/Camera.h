#pragma once
#include "RE\ReEng.h"
class Camera
{
private:
	matrix4 view;
	

	vector3 position;
	vector3 target;
	vector3 up;

	matrix4 projection;
	float fov;
	float aspect;
	float nearPlane;
	float farPlane;

	void UpdateView();
	void UpdateProjection();

public:
	Camera();
	~Camera();

	matrix4 GetView();
	matrix4 GetProjection(bool bOrthographic);
	
	void SetPosition(vector3 v3Position);
	void SetTarget(vector3 v3Target);

	void SetUp(vector3 v3Up);
	
	void MoveForward(float fIncrement);
	void MoveSideways(float fIncrement);
	void MoveVertical(float fIncrement);

	void ChangePitch(float fIncrement);
	void ChangeYaw(float fIncrement);
	void ChangeRoll(float fIncrement);
};


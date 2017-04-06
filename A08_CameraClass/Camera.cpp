#include "Camera.h"



void Camera::UpdateView()
{
	view = glm::lookAt(position, position+glm::normalize(target), glm::normalize(up));
}

void Camera::UpdateProjection()
{
	projection = glm::perspective(fov, aspect, nearPlane, farPlane);
}

Camera::Camera()
{
	target = vector3(0.f, 0.f, 1.f);
	up = vector3(0.f, 1.f, 0.f);
	position = vector3(0.f);

	fov = 3.14159f *.8f;
	aspect = (float)4 / (float)3;
	nearPlane = .01f;
	farPlane = 1000.f;

	UpdateView();
	UpdateProjection();

}

Camera::~Camera()
{
}

matrix4 Camera::GetView()
{
	return view;
}
matrix4 Camera::GetProjection(bool bOrthographic)
{
	if (bOrthographic)
		return IDENTITY_M4;
	else
		return projection;
}

void Camera::SetPosition(vector3 v3Position)
{
	position = v3Position;
	UpdateView();
}
void Camera::SetTarget(vector3 v3Target)
{
	target = v3Target;
	up = glm::normalize(glm::cross(glm::cross(target, up), target));
	UpdateView();
}

void Camera::SetUp(vector3 v3Up)
{
	up = v3Up;
	target = glm::normalize(glm::cross(up, glm::cross(target, up)));
	UpdateView();
}

void Camera::MoveForward(float fIncrement)
{
	position += glm::normalize(target)*fIncrement;
	UpdateView();
}
void Camera::MoveSideways(float fIncrement)
{
	vector3 side = glm::normalize(glm::cross(target, up))*fIncrement;
	position += side;
	UpdateView();
}
void Camera::MoveVertical(float fIncrement)
{
	position += glm::normalize(up)*fIncrement;
	UpdateView();
}

void Camera::ChangePitch(float fIncrement)
{
	vector3 side = glm::normalize(glm::cross(target, up));
	quaternion rotation = glm::angleAxis(glm::radians(fIncrement), side);

	target = rotation*target;
	up = rotation*up;
	UpdateView();
}
void Camera::ChangeYaw(float fIncrement)
{
	quaternion rotation = glm::angleAxis(glm::radians(fIncrement), glm::normalize(up));
	target = rotation*target;
	UpdateView();
}
void Camera::ChangeRoll(float fIncrement)
{
	quaternion rotation = glm::angleAxis(glm::radians(fIncrement), glm::normalize(target));
	up = rotation*up;
	UpdateView();
}
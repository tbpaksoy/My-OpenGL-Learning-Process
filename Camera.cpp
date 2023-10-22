#include "Camera.h"
#include <math.h>
#include <algorithm>
Camera::Camera(glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 up = glm::vec3(0, 0, 0), GLfloat yaw = YAW, GLfloat pitch = PITCH) :
	front(glm::vec3(0, 0, 1)), movementSpeed(SPEED), mouseSensivity(SENSITIVTY), zoom(ZOOM) 
{
	this->position = position;
	this->up = up;
	this->yaw = yaw;
	this->pitch = pitch;
	this->UpdateCameraVectors();
}
glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(this->position, this->position + this->front, this->up);
}
void Camera::ProcessKeyboard(CameraMovement direction, GLfloat deltaTime)
{
	GLfloat velocity = this->movementSpeed * deltaTime;

	switch(direction)
	{
	case FORWARD:
		position += front * velocity;
		break;
	case BACKWARD:
		position -= front * velocity;
		break;
	case RIGHT:
		position += right * velocity;
		break;
	case LEFT:
		position -= right * velocity;
		break;
	}
}
void Camera::ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constraintPitch = false)
{
	xOffset *= mouseSensivity;
	yOffset *= mouseSensivity;

	yaw += xOffset;
	pitch += yOffset;

	if (constraintPitch) pitch = std::clamp(pitch,-89.0f, 89.0f);

	UpdateCameraVectors();

	if (zoom >= 1.0f && zoom <= 45.0f)zoom -= yOffset;
	zoom = std::clamp(zoom, 1.0f, 45.0f);
}
float Camera::GetZoom()
{
	return zoom;
}
void Camera::UpdateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->front = glm::normalize(front);
	right = glm::normalize(glm::cross(this->front, this->worldUp));
	up = glm::normalize(glm::cross(right, this->front));
}
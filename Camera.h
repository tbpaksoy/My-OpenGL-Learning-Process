#pragma once

#include <vector>

#define GLEW_STATIC;
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 6.0f;
const GLfloat SENSITIVTY = 0.25f;
const GLfloat ZOOM = 45.0f;

class Camera
{
private:
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 worldUp;
    GLfloat yaw;
    GLfloat pitch;
    GLfloat movementSpeed;
    GLfloat mouseSensivity;
    GLfloat zoom;
    void UpdateCameraVectors();
public:
    Camera(glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 up = glm::vec3(0, 0, 0), GLfloat yaw = YAW, GLfloat pitch = PITCH);
    glm::mat4 GetViewMatrix();
    void ProcessKeyboard(CameraMovement direction, GLfloat deltaTime);
    void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constraintPitch = false);
    float GetZoom();
};
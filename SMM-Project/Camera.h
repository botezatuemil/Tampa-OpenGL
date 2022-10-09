#pragma once
#include <GL/glew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Model.h"

#include <vector>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    glm::mat4 GetViewMatrix();
    //void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessKeyboard(Camera_Movement direction, float deltaTime,  const std::vector<std::vector<glm::vec3>>& meshAndVertises);

    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(float yoffset);
    void SetCameraPosition(glm::vec3 position);
    bool canMove(glm::vec3 position,  const std::vector<std::vector<glm::vec3>>& meshAndVertises);

private:

    void updateCameraVectors();
};
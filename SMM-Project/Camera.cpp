#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Front, Up);
}

bool Camera::canMove(glm::vec3 position, const std::vector<std::vector<glm::vec3>>& meshAndVertises) {
	float minim = INT_MAX;

	for (const auto& mesh : meshAndVertises) {

		for (const auto& vertex : mesh) {

			float dis = hypot(hypot(position.x - vertex.x,
				position.y - vertex.y), position.z - vertex.z);

			if (dis <= 0.3)
				return false;
		}
	}
	return true;
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime,
	const std::vector<std::vector<glm::vec3>>& meshAndVertises)
{
	//const int timerLimit = 20;
	//static int timer = 0;

	float velocity = MovementSpeed * deltaTime;
	glm::vec3 testPos = Position;

	if (direction == FORWARD)
		testPos += Front * velocity;
	if (direction == BACKWARD)
		testPos -= Front * velocity;
	if (direction == LEFT)
		testPos -= Right * velocity;
	if (direction == RIGHT)
		testPos += Right * velocity;

	if (canMove(testPos, meshAndVertises))
		Position = testPos;
	/*else
	{
		if (timer > timerLimit)
		{
			Position.y += 0.5;
			timer = 0;
		}
		else ++timer;
	}*/
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	Zoom -= (float)yoffset;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.0f)
		Zoom = 45.0f;
}

void Camera::SetCameraPosition(glm::vec3 position)
{
	Position = position;
}


void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}
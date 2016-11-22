#ifndef CAMERA3D_H
#define CAMERA3D_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Directions
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const GLfloat PITCH_DEFAULT = -90.0f;
const GLfloat YAW_DEFAULT = 0.0f;
const GLfloat PAN_SPEED_DEFAULT = 0.01f;
const GLfloat SENSITIVITY_DEFAULT = 0.25f;
const GLfloat V_FOV_DEFAULT = 60.0f;

class ThreeD_Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Target;	
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	GLfloat Pitch;
	GLfloat Yaw;
	GLfloat Distance;

	GLfloat PanSpeed;
	GLfloat MouseSensitivity;
	GLfloat Fov;

	ThreeD_Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW_DEFAULT, GLfloat pitch = PITCH_DEFAULT) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), Target(glm::vec3(0.0f, 0.0f, 0.0f)), PanSpeed(PAN_SPEED_DEFAULT), MouseSensitivity(SENSITIVITY_DEFAULT), Fov(V_FOV_DEFAULT)
	{
		this->Position = position;
		this->WorldUp = up;
		this->Yaw = yaw;
		this->Pitch = pitch;
		Distance = glm::length(this->Position - this->Target);
		this->updateCameraVectors();
	}

	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(this->Position, this->Target, this->Up);
	}

	void move_camera(GLfloat deltaX, GLfloat deltaY)
	{
		//Reduce strength of mouse movement
		deltaX *= this->MouseSensitivity;
		deltaY *= this->MouseSensitivity;

		this->Yaw += deltaX;
		this->Pitch += deltaY;

		if (this->Pitch > 89.0f)
			this->Pitch = 89.0f;
		else if (this->Pitch < -89.0f)
			this->Pitch = -89.0f;

		updateCameraVectors();
	}

	void scroll_input(GLfloat deltaY)
	{
		if (this->Distance >= 1.0f)
			this->Distance -= deltaY * MouseSensitivity;

		if (this->Distance < 1.0f)
			this->Distance = 1.0f;

		updateCameraVectors();
	}

	void pan_camera(GLfloat deltaX, GLfloat deltaY)
	{
		//Reduce strength of mouse movement
		deltaX *= this->PanSpeed;
		deltaY *= this->PanSpeed;

		this->Target -= this->Up * deltaY;
		this->Target -= this->Right * deltaX;

		updateCameraVectors();
	}

private:

	void updateCameraVectors()
	{
		glm::vec3 cameraFront;
		cameraFront = glm::vec3(cos(glm::radians(this->Pitch)) * cos(glm::radians(this->Yaw)), sin(glm::radians(this->Pitch)), cos(glm::radians(this->Pitch)) * sin(glm::radians(this->Yaw)));

		this->Front = glm::normalize(cameraFront);
		this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));
		this->Up = glm::normalize(glm::cross(this->Right, this->Front));

		this->Position = this->Target - Distance * this->Front;
	}
};

#endif

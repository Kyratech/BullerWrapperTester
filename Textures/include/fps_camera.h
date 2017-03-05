#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>

#include "SimpleBulletWrapper\include\glm\glm.hpp"
#include "SimpleBulletWrapper\include\glm\gtc\matrix_transform.hpp"

enum Camera_Directions
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const GLfloat PITCH_DEFAULT = -90.0f;
const GLfloat YAW_DEFAULT = 0.0f;
const GLfloat PAN_SPEED_DEFAULT = 5.0f;
const GLfloat SENSITIVITY_DEFAULT = 0.25f;

class FPS_Camera
{
	public:
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;

		GLfloat Pitch;
		GLfloat Yaw;

		GLfloat MovementSpeed;
		GLfloat MouseSensitivity;

		FPS_Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW_DEFAULT, GLfloat pitch = PITCH_DEFAULT) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(PAN_SPEED_DEFAULT), MouseSensitivity(SENSITIVITY_DEFAULT)
		{
			this->Position = position;
			this->WorldUp = up;
			this->Yaw = yaw;
			this->Pitch = pitch;
			this->updateCameraVectors();
		}

		glm::mat4 GetViewMatrix()
		{
			return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
		}

		void mouse_input(GLfloat deltaX, GLfloat deltaY)
		{
			//Reduce strength of mouse movement
			GLfloat sensitivity = 0.05f;
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

		void keyboard_input(Camera_Directions direction, GLfloat deltaTime)
		{
			glm::vec3 frontGrounded(this->Front.x, 0.0f, this->Front.z);
			glm::vec3 rightGrounded(this->Right.x, 0.0f, this->Right.z);

			GLfloat cameraSpeed = this->MovementSpeed * deltaTime;
			if (direction == FORWARD)
				this->Position += frontGrounded * cameraSpeed;
			if (direction == BACKWARD)
				this->Position -= frontGrounded * cameraSpeed;
			if (direction == LEFT)
				this->Position -= rightGrounded * cameraSpeed;
			if (direction == RIGHT)
				this->Position += rightGrounded * cameraSpeed;
		}

	private:

		void updateCameraVectors()
		{
			glm::vec3 cameraFront;
			cameraFront = glm::vec3(cos(glm::radians(this->Pitch)) * cos(glm::radians(this->Yaw)), sin(glm::radians(this->Pitch)), cos(glm::radians(this->Pitch)) * sin(glm::radians(this->Yaw)));
			
			//Because this is a FPS camera, constrain movement on the Y-axis
			this->Front = glm::normalize(cameraFront);

			this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));
			this->Up = glm::normalize(glm::cross(this->Right, this->Front));
		}
};



#endif

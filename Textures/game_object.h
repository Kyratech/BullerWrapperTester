#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

//OpenGL stuff
#include <GL/glew.h>

//GLM - Maths for openGL
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Physics
#include "btBulletDynamicsCommon.h"
#include "SimpleBulletWrapper\PhysicsObject.h"

//Other
#include "mesh.h"
#include "shader.h"

#include <vector>

class GameObject
{
	public:
		Mesh *mesh;
		glm::vec3 position;
		PhysicsObject* physicsObject;
		glm::vec3 initialWorldPosition;
		glm::quat initialWorldQuaternion;

		GameObject(Mesh* myMesh, glm::vec3 offsetPosition, PhysicsObject* myPhysicsObject)
		{
			mesh = myMesh;
			position = offsetPosition;
			physicsObject = myPhysicsObject;

			//Store the initial position in case the simulation wants to restart
			initialWorldPosition = physicsObject->getPosition();
			initialWorldQuaternion = physicsObject->getRotationQuaternion();
		}

		void DrawObject(GLuint modelUniformLocation, Shader shader, glm::vec3 lightPos)
		{
			//Apply the translations on the model
			glm::mat4 modelTransform;

			glm::vec3 objectPosition = this->physicsObject->getPosition();
			glm::quat objectRotation = this->physicsObject->getRotationQuaternion();

			modelTransform = glm::translate(modelTransform, position);
			modelTransform = glm::translate(modelTransform, glm::vec3(objectPosition.x, objectPosition.y, objectPosition.z));


			modelTransform = glm::rotate(modelTransform, glm::angle(objectRotation), glm::axis(objectRotation));

			glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(modelTransform));

			//Calculate the normal matrix for the vertices
			glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelTransform)));
			GLint normalMatrixLoc = glGetUniformLocation(shader.getShaderProgram(), "normal_matrix");
			glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));

			//Draw the mesh
			mesh->Draw(shader, lightPos);
		}
};

#endif
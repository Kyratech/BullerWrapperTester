#ifndef GL_MESH_H
#define GL_MESH_H

#include <GL/glew.h>

//GLM - Maths for openGL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

#include <vector>

class Mesh
{
	public:
		std::vector<GLfloat> vertices;
		std::vector<GLuint> indices;
		glm::vec4 colour;

		//Constructor
		Mesh(std::vector<GLfloat> myVertices, std::vector<GLuint> myIndices, glm::vec4 myColour)
		{
			this->vertices = myVertices;
			this->indices = myIndices;
			this->colour = myColour;

			this->setupMesh();
		}

		void Draw(Shader myShader, glm::vec3 lightPos)
		{
			GLint fragmentColourLocation = glGetUniformLocation(myShader.getShaderProgram(), "fragment_colour");
			GLint lightColourLocation = glGetUniformLocation(myShader.getShaderProgram(), "light_colour");
			GLint lightPositionLocation = glGetUniformLocation(myShader.getShaderProgram(), "light_position");

			glUniform3f(fragmentColourLocation, colour.x, colour.y, colour.z);
			glUniform3f(lightColourLocation, 1.0f, 1.0f, 1.0f);
			glUniform3f(lightPositionLocation, lightPos.x, lightPos.y, lightPos.z);

			glBindVertexArray(this->VAO);
			glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

	private:
		GLuint VAO, VBO, EBO;
		
		//Initialises the buffer objects
		void setupMesh()
		{
			glGenVertexArrays(1, &this->VAO);
			glGenBuffers(1, &this->VBO);
			glGenBuffers(1, &this->EBO);

			//Set up the vertex buffers
			glBindVertexArray(this->VAO);
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(GLfloat), &this->vertices[0], GL_STATIC_DRAW);

			//Set up the element buffers
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

			//Set the vertex attrib pointers
			//Vertex positions
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);
			//Vertex normals
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);

			glBindVertexArray(0);
		}
};

#endif
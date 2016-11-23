//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

//SOIL - Image loading
#include <SOIL/soil.h>

//GLM - Maths for openGL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Physics
#include "btBulletDynamicsCommon.h"
#include "SimpleBulletWrapper\PhysicsObjectTypes.h"
#include "SimpleBulletWrapper\PhysicsWorld.h"

//GUI
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw_gl3.h"

//Other
#include "shader.h"
#include "3d_camera.h"
#include "mesh.h"
#include "game_object.h"
#include "cube_mesh.h"
#include "plane_mesh.h"
#include "cone_mesh.h"
#include "cylinder_mesh.h"

#include <iostream>
#include<vector>

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouse_movement(GLFWwindow *window, double xPos, double yPos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xpos, double ypos);

const GLuint WIDTH = 1400;
const GLuint HEIGHT = 800;

//-----------------//
//Set up the camera//
//-----------------//

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

ThreeD_Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;

bool firstMouseInput = true;

//Mouse button flags
bool middleMouse = false;

//Key pressed flags
bool keys[1024];

//For calculating delta time
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

bool simulationRunning = false;

int main()
{
	//========================//
	//Set up the OpenGL window//
	//========================//

	//Start up glfw
	glfwInit();
	//Using version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Raises errors when trying to use outdated OpenGL functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Take a guess
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//Window pointer object holds windowing data
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "I've yet to find someone who can outsmart the Bullet", nullptr, nullptr);
	//Exit if the window could not be created
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	//Thingy to ficus on this window
	glfwMakeContextCurrent(window);
	
	//Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_movement);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	//Draw wireframes
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	//Set mouse capture
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	//Use modern techniquies to manage OpenGL functionality
	glewExperimental = GL_TRUE;
	//Exit if GLEW broke
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialise GLEW" << std::endl;
		return -1;
	}

	/*Tell openGL what size the viewport is going to be, and where 0,0 is at (lower-left)
	*Location is on the axis (-1 <= x <= 1, -1 <= y <= 1), so we basically
	*map from (-1, 1) to (0, 800) and (0, 600)*/
	glViewport(0, 0, WIDTH, HEIGHT);

	//Turn on depth testing
	glEnable(GL_DEPTH_TEST);

	//Shader load
	Shader ourShader("./vertex_shader.txt", "./fragment_shader.txt");

	//============//
	//Set up ImGUI//
	//============//

	ImGui_ImplGlfwGL3_Init(window, false);
	bool show_guiWindow = true;

	//=========================//
	//Set up the physics engine//
	//=========================//

	/*
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();

	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -10, 0));
	*/

	PhysicsWorld* world = new PhysicsWorld(glm::vec3(0, -10, 0));

	//==================//
	//Set up the objects//
	//==================//

	//Physics bits

	std::vector<GameObject> dynamicObjects;

	//Ground
	/*
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);

	Mesh planeMesh(getXZPlaneVertices(20.0f), getPlaneIndices(), glm::vec4(0.0f, 0.2f, 0.8f, 1.0f));
	Physics_Object planeObject(&planeMesh, glm::vec3(0.0f, 1.0f, 0.0f), groundRigidBody, dynamicsWorld);
	
	float groundBoxDimension = 10.0f;
	btCollisionShape* groundShape = new btBoxShape(btVector3(groundBoxDimension / 2.0, groundBoxDimension / 2.0, groundBoxDimension / 2.0));
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -5, 0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0,0,0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);

	Mesh bigcubeMesh(getCubeVertices(groundBoxDimension), getCubeIndices(), glm::vec4(0.0f, 0.3f, 0.8f, 1.0f));
	GameObject bigcubeObject(&bigcubeMesh, glm::vec3(0.0f, 0.0f, 0.0f), groundRigidBody, dynamicsWorld);

	//Box
	float boxDimension = 0.5f;
	btCollisionShape* fallShape = new btBoxShape(btVector3(boxDimension / 2.0, boxDimension / 2.0, boxDimension / 2.0));
	btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0.5, 0.5, 0, 4), btVector3(0, 5, 0)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);

	Mesh cubeMesh(getCubeVertices(boxDimension), getCubeIndices(), glm::vec4(1.0f, 0.3f, 0.0f, 1.0f));
	GameObject cubeObject(&cubeMesh, glm::vec3(0.0f, 0.0f, 0.0f), fallRigidBody, dynamicsWorld);

	//Another box
	boxDimension = 1.0f;
	btCollisionShape* fallShape2 = new btBoxShape(btVector3(boxDimension / 2.0, boxDimension / 2.0, boxDimension / 2.0));
	btDefaultMotionState* fallMotionState2 = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 7, 0)));
	btScalar mass2 = 0.5;
	btVector3 fallInertia2(0, 0, 0);
	fallShape->calculateLocalInertia(mass2, fallInertia2);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI2(mass2, fallMotionState2, fallShape2, fallInertia2);
	btRigidBody* fallRigidBody2 = new btRigidBody(fallRigidBodyCI2);

	Mesh cubeMesh2(getCubeVertices(boxDimension), getCubeIndices(), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	GameObject cubeObject2(&cubeMesh2, glm::vec3(0.0f, 0.0f, 0.0f), fallRigidBody2, dynamicsWorld);
	*/

	PhysicsBox groundBox(false, 10.0, 10.0, 10.0, 10.0, glm::vec3(0, -5, 0), glm::vec3(0, 0, 0), false, world);
	Mesh groundMesh(getCubeVertices(10.0), getCubeIndices(), glm::vec4(0.0f, 0.2f, 0.8f, 1.0f));
	GameObject groundObject(&groundMesh, glm::vec3(0.0, 0.0, 0.0), &groundBox);

	PhysicsBox bigBox(true, 1.0, 1.0, 1.0, 1.0, glm::vec3(0, 10, 5), glm::vec3(45, 0, 0), false, world);
	Mesh bigBoxMesh(getCubeVertices(1.0), getCubeIndices(), glm::vec4(1.0f, 0.3f, 0.0f, 1.0f));
	GameObject bigBoxObject(&bigBoxMesh, glm::vec3(0.0f, 0.0f, 0.0f), &bigBox);

	PhysicsCylinder littleCylinder(true, 1, 1, 1, 1, glm::vec3(0, 5, 0), glm::vec3(80, 0, 90), false, world);
	Mesh littleBoxMesh(getCylinderVertices(1, 1, 1), getConeIndices(), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	GameObject littleBoxObject(&littleBoxMesh, glm::vec3(0.0, 0.0, 0.0), &littleCylinder);



	//==============//
	//Light position//
	//==============//

	glm::vec3 globalLightPosition(5.0f, 5.0f, 5.0f);

	//===============//
	//Simulation loop//
	//===============//

	/*Game loop keeps running so that the window doesn't just quit.*/
	while (!glfwWindowShouldClose(window))
	{
		//Calculate the time since the last frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//Check for events (Eg. keyboard, mouse input)
		//Usually call event processing at the start of a loop iteration
		glfwPollEvents();

		//======================//
		// ImGUI interface code //
		//======================//
		ImGui_ImplGlfwGL3_NewFrame();	

		ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
		ImGui::Begin("GUI Window", &show_guiWindow);

		ImGui::Text("Hello, world!");
		
		static float stepsPerSecond = 60.0f;
		ImGui::SliderFloat("Simulation steps per second", &stepsPerSecond, 1.0f, 240.0f);

		ImGui::Checkbox("Run simulation", &simulationRunning);

		if (ImGui::Button("Reset"))
		{
			littleCylinder.resetTransform();
			bigBox.resetTransform();

			//Brief update to move the objects even if simulation isn't running
			world->stepWorld(1 / 1000);
		}
		
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();

		//RENDERING COMMANDS HERE
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.Use();

		GLint fragmentColourLocation = glGetUniformLocation(ourShader.getShaderProgram(), "fragment_colour");
		

		//===================================//
		//Create a transformation in 3D space//
		//===================================//
		//(stolen code)

		//Generate the view matrix
		glm::mat4 view;
		view = camera.GetViewMatrix();
		
		//Generate the projection matrix
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.Fov), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 1000.0f);

		// Get their uniform location
		GLint modelLoc = glGetUniformLocation(ourShader.getShaderProgram(), "model");
		GLint viewLoc = glGetUniformLocation(ourShader.getShaderProgram(), "view");
		GLint projLoc = glGetUniformLocation(ourShader.getShaderProgram(), "projection");
		
		
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	
		
		//================//
		// Run simulation //
		//================//

		if(simulationRunning)
			world->stepWorld(1 / stepsPerSecond);

		//==============//
		// Draw objects //
		//==============//

		groundObject.DrawObject(modelLoc, ourShader, globalLightPosition);
		bigBoxObject.DrawObject(modelLoc, ourShader, globalLightPosition);
		littleBoxObject.DrawObject(modelLoc, ourShader, globalLightPosition);

		// ImGui functions end here
		ImGui::Render();
		
		//Swap the colour buffer used to draw, and show output on the screen
		glfwSwapBuffers(window);
	}

	/*
	//Clean up the physics engine assets
	bigcubeObject.DeleteObject(dynamicsWorld);
	cubeObject.DeleteObject(dynamicsWorld);
	cubeObject2.DeleteObject(dynamicsWorld);

	delete fallShape;
	//delete groundShape;
	
	delete dynamicsWorld;
	delete solver;
	delete collisionConfiguration;
	delete dispatcher;
	delete broadphase;
	*/

	delete world;

	//Clean out all of the resources we allocated
	glfwTerminate();

	return 0;
}

/*
* Record the states of keys when one changes
*/
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	//Check to see if a new key has been pressed or released
	if (action == GLFW_PRESS)
	{
		keys[key] = true;

		if (key == GLFW_KEY_SPACE)
		{
			simulationRunning = !simulationRunning;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		keys[key] = false;
	}
	
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.scroll_input(yoffset);
}

/*
* Record the changes in position of the mouse, use it to update the camera
*/
void mouse_movement(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouseInput)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouseInput = false;
	}

	//Difference between current moose position and previous
	GLfloat deltaX = xPos - lastX;
	GLfloat deltaY = lastY - yPos;
	
	//Update previous
	lastX = xPos;
	lastY = yPos;

	if (middleMouse)
	{
		if (keys[GLFW_KEY_LEFT_SHIFT])
			camera.pan_camera(deltaX, deltaY);
		else
			camera.move_camera(deltaX, deltaY);
	}
}

/*
* Record the state of the middle mouse when it changes
*/
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
		middleMouse = true;
	else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
		middleMouse = false;
}

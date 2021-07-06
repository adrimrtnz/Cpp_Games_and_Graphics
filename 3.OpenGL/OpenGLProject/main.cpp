#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


// custom classes
#include "ShaderLoader.h"
#include "Camera.h"
#include "LightRenderer.h"
#include "MeshRenderer.h"
#include "TextureLoader.h"

// bullet physics library
#include <btBulletDynamicsCommon.h>

Camera* camera;
LightRenderer* light;

MeshRenderer* sphere;

btDiscreteDynamicsWorld* dynamicsWorld;

// camera and screen attributes
const int WIDTH = 800;
const int HEIGTH = 600;
const float FOV = 45.0f;
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 100.0f;

const float GRAVITY_ACCELERATION = -9.8f;
const float ROTATION = 0;
const float RIGIDBODY_DISTANCE = 10.0f;

// ball object attributes
float sphereMass = 10.0;
float sphereRestitution = 1.0f;
float sphereFriction = 1.0f;


// functions prototypes
void renderScene();
void initGame();
static void glfwError(int id, const char* description);
//void addRigidBodies();

int main(int argc, char** argv) {
	
	glfwSetErrorCallback(&glfwError);

	glfwInit();

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGTH, "OpenGL first steps", NULL, NULL);
	
	glfwMakeContextCurrent(window);
	glewInit();
	initGame();

	auto previousTime = std::chrono::high_resolution_clock::now();

	// keep the window working until it's close
	while (!glfwWindowShouldClose(window)) {

		auto currentTime = std::chrono::high_resolution_clock::now();
		float dt = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - previousTime).count();
		dynamicsWorld->stepSimulation(dt);

		// render the scene
		renderScene();

		glfwSwapBuffers(window);			// the display buffer is where the current frame is rendered and stored
		glfwPollEvents();

		previousTime = currentTime;
	}

	glfwTerminate();

	delete camera;
	delete light;


	return 0;
}

void initGame() {

	glEnable(GL_DEPTH_TEST);

	ShaderLoader shader;

	GLuint flatShaderProgram = shader.createProgram("Assets/Shaders/FlatModel.vs", "Assets/Shaders/FlatModel.fs");
	GLuint texturedShaderProgram = shader.createProgram("Assets/Shaders/TexturedModel.vs", "Assets/Shaders/TexturedModel.fs");
	
	camera = new Camera(FOV, WIDTH, HEIGTH, NEAR_PLANE, FAR_PLANE, glm::vec3(0.0f, 4.0f, 20.0f));
	
	light = new LightRenderer(MeshType::kCube, camera);
	light->setProgram(flatShaderProgram);
	light->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	TextureLoader tLoader;

	GLuint sphereTexture = tLoader.getTextureID("Assets/Textures/balldimpled.png");

	// init physics
	btBroadphaseInterface* bradphase = new btDbvtBroadphase();
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

	// create a new dynamicWorld
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, bradphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, GRAVITY_ACCELERATION, 0));

	// to be moved
	btCollisionShape* sphereShape = new btSphereShape(1.0f);
	btDefaultMotionState* sphereMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(ROTATION, RIGIDBODY_DISTANCE, 0)));

	btScalar mass = sphereMass;
	btVector3 sphereInertia(0, 0, 0);
	sphereShape->calculateLocalInertia(mass, sphereInertia);

	btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(mass, sphereMotionState, sphereShape, sphereInertia);
	btRigidBody* sphereRigidBody = new btRigidBody(sphereRigidBodyCI);
	sphereRigidBody->setRestitution(sphereRestitution);
	sphereRigidBody->setFriction(sphereFriction);

	dynamicsWorld->addRigidBody(sphereRigidBody);

	// sphere Mesh
	sphere = new MeshRenderer(MeshType::kSphere, camera, sphereRigidBody);
	sphere->setProgram(texturedShaderProgram);
	sphere->setTexture(sphereTexture);
	sphere->setScale(glm::vec3(1.0f));
	// end of "to be moved"
}

/*
void addRigidBodies() {
	
	btCollisionShape* sphereShape = new btSphereShape(1.0f);
	btDefaultMotionState* sphereMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(ROTATION, RIGIDBODY_DISTANCE, 0)));

	btScalar mass = sphereMass;
	btVector3 sphereInertia(0, 0, 0);
	sphereShape->calculateLocalInertia(mass, sphereInertia);

	btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(mass, sphereMotionState, sphereShape, sphereInertia);
	btRigidBody* sphereRigidBody = new btRigidBody(sphereRigidBodyCI);
	sphereRigidBody->setRestitution(sphereRestitution);
	sphereRigidBody->setFriction(sphereFriction);

	dynamicsWorld->addRigidBody(sphereRigidBody);
}
*/

void renderScene() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// This function clears the buffer
	glClearColor(38/255.0, 38/255.0, 39/255.0, 1.0);	// RGBA between 0.0 and 1.0

	// Draw game objects here
	//light->draw();
	sphere->draw();
}

static void glfwError(int id, const char* description) {
	std::cout << "Problem Description: " << description << std::endl;
}
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
MeshRenderer* ground;
MeshRenderer* enemy;

btDiscreteDynamicsWorld* dynamicsWorld;

GLuint flatShaderProgram;
GLuint texturedShaderProgram;
GLuint sphereTexture, enemyTexture, groundTexture;

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

// enemy object attributes
float enemyRestitution = 0.0f;
float enemyFriction = 1.0f;

// ground object attributes
float groundFriction = 1.0f;
float groundRestitution = 0.9f;


// functions prototypes
void renderScene();
void initGame();
static void glfwError(int id, const char* description);
void addRigidBodies();
void myTickCallBack(btDynamicsWorld* dynamicsWorld, btScalar timeStep);

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

	flatShaderProgram = shader.createProgram("Assets/Shaders/FlatModel.vs", "Assets/Shaders/FlatModel.fs");
	texturedShaderProgram = shader.createProgram("Assets/Shaders/TexturedModel.vs", "Assets/Shaders/TexturedModel.fs");
	
	camera = new Camera(FOV, WIDTH, HEIGTH, NEAR_PLANE, FAR_PLANE, glm::vec3(0.0f, 4.0f, 20.0f));
	
	light = new LightRenderer(MeshType::kCube, camera);
	light->setProgram(flatShaderProgram);
	light->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	TextureLoader tLoader;

	sphereTexture = tLoader.getTextureID("Assets/Textures/balldimpled.png");
	groundTexture = tLoader.getTextureID("Assets/Textures/ground.jpg");
	enemyTexture = tLoader.getTextureID("Assets/Textures/tennisBall.jpg");

	// init physics
	btBroadphaseInterface* bradphase = new btDbvtBroadphase();
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

	// create a new dynamicWorld
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, bradphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, GRAVITY_ACCELERATION, 0));
	dynamicsWorld->setInternalTickCallback(myTickCallBack);

	addRigidBodies();
}

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

	sphereRigidBody->setActivationState(DISABLE_DEACTIVATION);

	dynamicsWorld->addRigidBody(sphereRigidBody);

	// sphere Mesh
	sphere = new MeshRenderer(MeshType::kSphere, "hero", camera, sphereRigidBody);
	sphere->setProgram(texturedShaderProgram);
	sphere->setTexture(sphereTexture);
	sphere->setScale(glm::vec3(1.0f));

	sphereRigidBody->setUserPointer(sphere);

	// ground platform RigidBody
	btCollisionShape* groundShape = new btBoxShape(btVector3(4.0f, 0.5f, 4.0f));
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -2.0f, 0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0.0f, new btDefaultMotionState(), groundShape, btVector3(0, 0, 0));

	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	groundRigidBody->setFriction(groundFriction);
	groundRigidBody->setRestitution(groundRestitution);
	groundRigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);

	dynamicsWorld->addRigidBody(groundRigidBody);

	// ground platform Mesh
	ground = new MeshRenderer(MeshType::kCube, "ground", camera, groundRigidBody);
	ground->setProgram(texturedShaderProgram);
	ground->setTexture(groundTexture);
	ground->setScale(glm::vec3(10.0f, 0.0f, 7.0f));

	groundRigidBody->setUserPointer(ground);

	// Enemy RigidBody
	btCollisionShape* shape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
	btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(18.0f, 1.0f, 0)));
	btRigidBody::btRigidBodyConstructionInfo rbCI(0.0f, motionState, shape, btVector3(0.0f, 0.0f, 0.0f));

	btRigidBody* rb = new btRigidBody(rbCI);
	rb->setFriction(enemyFriction);
	rb->setRestitution(enemyRestitution);

	//rb->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
	rb->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);

	dynamicsWorld->addRigidBody(rb);

	// Enemy Mesh
	enemy = new MeshRenderer(MeshType::kSphere, "enemy", camera, rb);
	enemy->setProgram(texturedShaderProgram);
	enemy->setTexture(enemyTexture);
	enemy->setScale(glm::vec3(1.0f, 1.0f, 1.0f));

	rb->setUserPointer(enemy);
}

void renderScene() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// This function clears the buffer
	glClearColor(38/255.0, 38/255.0, 39/255.0, 1.0);	// RGBA between 0.0 and 1.0

	// Draw game objects here
	//light->draw();
	sphere->draw();
	ground->draw();
	enemy->draw();
}

void myTickCallBack(btDynamicsWorld* dynamicsWorld, btScalar timeStep) {
	
	// Get enemy transform
	btTransform t(enemy->rigidBody->getWorldTransform());

	// Set enemy position
	t.setOrigin(t.getOrigin() + btVector3(-15, 0, 0) * timeStep);

	// Check if offScreen
	if (t.getOrigin().x() <= -18.f) {
		t.setOrigin(btVector3(18, 1, 0));
	}
	
	enemy->rigidBody->setWorldTransform(t);
	enemy->rigidBody->getMotionState()->setWorldTransform(t);

	// Check for collisions
	int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();

	for (int i = 0; i < numManifolds; i++) {
		
		btPersistentManifold* contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);

		int numContacts = contactManifold->getNumContacts();

		if (numContacts > 0) {

			const btCollisionObject *OBJ_A = contactManifold->getBody0();
			const btCollisionObject *OBJ_B = contactManifold->getBody1();

			MeshRenderer* gModA = (MeshRenderer*)OBJ_A->getUserPointer();
			MeshRenderer* gModB = (MeshRenderer*)OBJ_B->getUserPointer();

			//printf("gModA: %s, gModB %s \n", gModA->name, gModB->name);

			if ((gModA->name == "hero" && gModB->name == "enemy") ||
				(gModA->name == "enemy" && gModB->name == "hero")) {

				printf("Collision: %s with %s \n", gModA->name, gModB->name);

				if (gModB->name == "enemy") {
					btTransform b(gModB->rigidBody->getWorldTransform());
					b.setOrigin(btVector3(18, 1, 0));
					gModB->rigidBody->setWorldTransform(b);
					gModB->rigidBody->getMotionState()->setWorldTransform(b);
				}
				else {
					btTransform a(gModA->rigidBody->getWorldTransform());
					a.setOrigin(btVector3(18, 1, 0));
					gModA->rigidBody->setWorldTransform(a);
					gModA->rigidBody->getMotionState()->setWorldTransform(a);
				}


				if ((gModA->name == "hero" && gModB->name == "ground") ||
					(gModA->name == "ground" && gModB->name == "hero")) {

					printf("Collision: %s with %s \n", gModA->name, gModB->name);
				}
			}
		}
	}
}

static void glfwError(int id, const char* description) {
	std::cout << "Problem Description: " << description << std::endl;
}
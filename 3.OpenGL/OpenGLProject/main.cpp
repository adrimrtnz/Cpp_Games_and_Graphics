#include <GL/glew.h>
#include <GLFW/glfw3.h>


// custom classes
#include "ShaderLoader.h"
#include "Camera.h"
#include "LightRenderer.h"

Camera* camera;
LightRenderer* light;

// camera and screen attributes
const int WIDTH = 800;
const int HEIGTH = 600;
const float FOV = 45.0f;
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 100.0f;

// functions prototypes
void renderScene();
void initGame();
static void glfwError(int id, const char* description);

int main(int argc, char** argv) {
	
	glfwSetErrorCallback(&glfwError);

	glfwInit();

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGTH, "OpenGL first steps", NULL, NULL);
	
	glfwMakeContextCurrent(window);
	glewInit();
	initGame();

	// keep the window working until it's close
	while (!glfwWindowShouldClose(window)) {

		// render the scene
		renderScene();

		glfwSwapBuffers(window);			// the display buffer is where the current frame is rendered and stored
		glfwPollEvents();

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

	camera = new Camera(FOV, WIDTH, HEIGTH, NEAR_PLANE, FAR_PLANE, glm::vec3(0.0f, 4.0f, 6.0f));
	light = new LightRenderer(MeshType::kTriangle, camera);
	light->setProgram(flatShaderProgram);
	light->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
}

void renderScene() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// This function clears the buffer
	glClearColor(104/255.0, 254/255.0, 183/255.0, 1.0);	// RGBA between 0.0 and 1.0

	// Draw game objects here
	light->draw();
}

static void glfwError(int id, const char* description) {
	std::cout << "Problem Description: " << description << std::endl;
}
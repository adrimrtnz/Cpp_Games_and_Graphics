#include <GL/glew.h>
#include <GLFW/glfw3.h>


// custom classes
#include "ShaderLoader.h"
#include "Camera.h"
#include "LightRenderer.h"

Camera* camera;
LightRenderer* light;

const int WIDTH = 800;
const int HEIGTH = 600;

// functions prototypes
void renderScene();
void initGame();

int main(int argc, char** argv) {
	
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGTH, "OpenGL first steps", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();

	// keep the window working until it's close
	while (!glfwWindowShouldClose(window)) {

		// render the scene
		renderScene();
		glfwSwapBuffers(window);			// the display buffer is where the current frame is rendered and stored
		glfwPollEvents();

	}

	glfwTerminate();

	return 0;
}

void initGame() {
	glEnable(GL_DEPTH_TEST);

	ShaderLoader shader;

	GLuint flatShaderProgram = shader.createProgram("Assets/Shaders/FlatModel.vs", "Assets/Shaders/FlatModel.fs");
}

void renderScene() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// This function clears the buffer
	glClearColor(104/255.0, 254/255.0, 183/255.0, 1.0);	// RGBA between 0.0 and 1.0

	// Draw game objects here
}
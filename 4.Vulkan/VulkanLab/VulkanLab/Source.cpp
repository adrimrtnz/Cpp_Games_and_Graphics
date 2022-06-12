#define GFLW_INCLUDE_VULKAN			// This must be added before including GLFW header
#include <GLFW/glfw3.h>

#include "Config.h"

int main() 
{

	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Project", nullptr, nullptr);

	while (!glfwWindowShouldClose(window)) 
	{
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
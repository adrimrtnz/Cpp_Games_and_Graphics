#define GFLW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

const int HEIGHT = 720;
const int WIDTH = 1280;

int main() {

	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Project", nullptr, nullptr);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
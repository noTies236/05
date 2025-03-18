// Lib
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
/* GLFW: It provides a simple interface for creating the program's window and (optionally) an OpenGL or Vulkan graphics context/device, and 
for receiving user input from various devices, including keyboard, mouse, controllers and joysticks. It provides this on many platforms, which 
is something that would otherwise take quite a while to program yourself.*/
#include <vector>

// Headers
#include "Pipeline/Pipeline.h"

int main() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(640, 480, "04", NULL, NULL);

	if (!window) {
		std::cout << "windows not created\n";
	}
	
	glfwMakeContextCurrent(window);

	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLAD has been inicialized!!! I'm glad :-)" << std::endl;
	} else {
		std::cout << "Falha ao inicializar GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwPollEvents();

		Pipeline::Draw();
	}

	glfwTerminate();

	return 1;
}
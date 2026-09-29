#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
	
	//Continue if glfw initialized succesfully, exit otherwise
	if (glfwInit() == GLFW_TRUE)
		std::cout << "glfw init success\n";
	else { 
		std::cout << "glfw init failed\n"; 
		return -1;
	}

	//Tell glfw the OpenGL version(4.6) and profile(CORE) and create a window named hilol
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* hilol = glfwCreateWindow(1600, 900, "Hello Window!", NULL, NULL);
	
	//Check if window was created successfully, exit otherwise
	if (!hilol) {
		std::cout << "window failed to create\n";
		return -1;
	}

	//Keep window open until the close button pressed
	while (!glfwWindowShouldClose(hilol))
	{
		//Poll window events such as resize, fullscreen, move (if not done, then the window will be frozen)
		glfwPollEvents();
	}
}
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

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
	glfwMakeContextCurrent(hilol);

	glfwSetFramebufferSizeCallback(hilol, framebuffer_size_callback);

	//initialize glad, quit if failed
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//Telling OpenGL the size of the viewport
	glViewport(0, 0, 1600, 900);

	//Coordinates of the triangle in NDC
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	//Vertex shader source
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	//Fragment shader source
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()"
		"{"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
		"}";

	//Creating and binding Vertex Array
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Generating and binding Vertex Buffer
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Passing data to VBO
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertices, GL_STATIC_DRAW);


	//Creating and compiling vertex shader from source
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//Creating and compiling fragment shader from source
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Creating shader program, attaching the vertex and fragment shaders to it, and using it
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//Check if window was created successfully, exit otherwise
	if (!hilol) {
		std::cout << "window failed to create\n";
		return -1;
	}

	//Keep window open until the close button pressed
	while (!glfwWindowShouldClose(hilol))
	{
		//Processing Input and Window events
		glfwPollEvents();
		processInput(hilol);
		
		//Clearing the screen before render
		glClearColor(0.5f, 0.3f, 3.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	
		//Rendering 
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		//Swapping front and back buffers
		glfwSwapBuffers(hilol);
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
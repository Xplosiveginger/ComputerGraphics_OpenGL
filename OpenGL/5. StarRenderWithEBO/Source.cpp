#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<cmath>
#include<ShaderH.h>
using namespace std;

void FrameBufferSizeCallBack(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

const unsigned int scrWidth = 640;
const unsigned int scrHeight = 640;

int main()
{
	// GLFW Initialization
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//

	// Window Creation
	GLFWwindow* window = glfwCreateWindow(scrWidth, scrHeight, "First Window", NULL, NULL);

	if (window == NULL)
	{
		cout << "Failed To Create Window." << endl;

		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallBack);
	//

	// Glad Initialization
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "GLAD not initialized" << endl;

		glfwTerminate();
		return -1;
	}
	//

	Shader TriShader = Shader("vertex.shader", "fragment.shader");
	Shader TriShader2 = Shader("vertex.shader", "fragment_two.shader");
	Shader TriShader3 = Shader("vertex.shader", "fragment_three.shader");
	Shader TriShader4 = Shader("vertex.shader", "fragment_four.shader");

	float vertices[] = {
		0.0f, 0.8f, 0.0f,   // 0
		0.3f, 0.3f, 0.0f,   // 1
		0.8f, 0.0f, 0.0f,   // 2
		0.3f, -0.3f, 0.0f,  // 3
		0.0f, -0.8f, 0.0f,  // 4
		-0.3f, -0.3f, 0.0f, // 5
		-0.8f, 0.0f, 0.0f,  // 6
		-0.3f, 0.3f, 0.0f,  // 7

		0.0f, 0.0f, 0.0f    // 8
	};

	unsigned int indices[] = {
		0, 1, 8,
		1, 2, 8,
		2, 3, 8,
		3, 4, 8,
		4, 5, 8,
		5, 6, 8,
		6, 7, 8,
		7, 0, 8
	};

	//VBO - Vertex Buffer Object || VAO - Vertex Array Object
	unsigned int VBO, VAO, EBO;

	//VBO Declaration
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//VAO Declaration
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//EBO Declaration
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // unbinding the current allocated VBO
	glBindVertexArray(0); // unbinding the current allocated VAO

	// Render Loop
	while (!glfwWindowShouldClose(window))
	{
		// Inputs
		ProcessInput(window);

		// Render
		glClearColor(1.0, 1.0, 1.0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		TriShader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

		TriShader2.use();
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)48);

		// BufferSwapping and Event Tracking
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void FrameBufferSizeCallBack(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
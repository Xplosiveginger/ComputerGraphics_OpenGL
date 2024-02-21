#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
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

	// Render Loop
	while (!glfwWindowShouldClose(window))
	{
		// Inputs
		ProcessInput(window);

		float time = sinf(glfwGetTime());
		//

		// Render
		glClearColor(time, cosf(time), time, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//

		// BufferSwapping and Event Tracking
		glfwSwapBuffers(window);
		glfwPollEvents();
		// 
	}
	//

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
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<cmath>
#include<ShaderH.h>
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>

void frameBufferSizeCallBack(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);
unsigned int GenerateTexture2D(GLint wrapMode);

const unsigned int SCR_WIDTH = 640;
const unsigned int SCR_HEIGHT = 640;

int main()
{
	//GLFW Initilization--------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//----------------------------------------

	//Window Creation------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "SQUARE RENDER", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "FAILED TO CREATE THE WINDOW!!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallBack);
	//---------------------------------------------
	//GLAD Initialization
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "GLAD is not initialized!!" << std::endl;
		glfwTerminate();
		return -1;
	}

	Shader myShader = Shader("Vertex.shader", "fragment.shader");

	// set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
	float vertices[] = {
		// positions          // colors           // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	//VBO - Vertex Buffer Object || VAO - Vertex Array Object || EBO - Element Buffer Object
	unsigned int VBO, VAO, EBO;

	//VBO Declaration
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//VAO Declaration
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//EBO Declaration
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GLint wrapMode = GL_CLAMP_TO_BORDER; // GL_REPEAT is the default mode
	unsigned int myTexture = GenerateTexture2D(wrapMode);
	
	// load and generate the texture
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("Grass.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glBindBuffer(GL_ARRAY_BUFFER, 0);// unbinding the current allocated VBO
	glBindVertexArray(0); // unbinding the current allocated VAO

	myShader.use();
	myShader.setInt("ourTexture", 0);

	//Render loop
	while (!glfwWindowShouldClose(window))
	{
		//Inputs
		ProcessInput(window);

		//Render
		glClearColor(0.6f, 0.5f, 0.8f, 1.0f);//RGBA Color space value
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
		glBindTexture(GL_TEXTURE_2D, myTexture);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//Buffer Swapping And Event Tracking
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate();
	return 0;
}

void frameBufferSizeCallBack(GLFWwindow* window, int width, int height)
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

unsigned int GenerateTexture2D(GLint wrapMode)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return texture;
}
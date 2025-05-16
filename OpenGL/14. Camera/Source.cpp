#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include<glad/glad.h>
#include<glfw/glfw3.h>

#include<ShaderH.h>
#include<iostream>
#include<cmath>
#include<CubeRender.h>
#include"Camera.h"
using namespace std;

unsigned int SCR_WIDTH = 960;
unsigned int SCR_HEIGHT = 540;

float lastX = SCR_WIDTH / 2;
float lastY = SCR_HEIGHT / 2;

Camera camera = Camera(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
Camera_Movement cameraDirection = Camera_Movement::NONE;

glm::vec2 resolution = glm::vec2(SCR_WIDTH, SCR_HEIGHT);
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::vec3 cameraTarget = glm::vec3(0.0f);
//glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
//glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
//glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
//glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight));

bool needColors = true;
bool needDistance = true;

void frameBufferSizeCallBack(GLFWwindow* window, int width, int height);
void ProcessInputs(GLFWwindow* window);
float ConvertToRGB(float val);
void ChangeFragShader(Shader shader, int selectedItem, float color1[4], float color2[4], float mul);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void ScrollCallback(GLFWwindow*, double xOffset, double yOffset);

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

bool captureMouse = false;
bool firstMouse = true;

//STARTING POINT OF OUR PROGRAM
int main()
{
	//INITIALIZE GLFW LIB's AND CONFIG.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Camera", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "FAILED TO CREATE THE WINDOW! " << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallBack);
	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetScrollCallback(window, ScrollCallback);

	//INITIALIZING GLAD FUNCTIONS
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "FAILED TO INITIALIZE GLAD!" << std::endl;
		glfwTerminate();
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	InitCubeVerts(0.0, 0.0f, 0.7f);

	//Initialize ImGui (Not needed for exams)
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	//ImGui variables
	bool draw = true;
	bool useTextures = true;
	
	float color1[] = { 1.0f, 0.5f, 0.0f, 1.0f };
	float color2[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float mul = 1.0f;

	static const char* items[]
	{ 
		"CheckerBoard",
		"CheckerBoardWithCircularGradient",
		"CircularWaveAnimated",
		"MarblePattern",
		"NoisePattern",
		"RadialGradient",
		"StripPattern",
		"WoodGrain" 
	};
	static int Selecteditem = 0;
	//*********************************
	
	// PreLoading Shaders (no need for this if you are not using ImGui)
	Shader checkerboardshader = Shader("vertex.shader", "checkerpatternfrag.shader");
	Shader checkerboardwithcirculargradientshader = Shader("vertex.shader", "checkerboardwithcirculargradiantfrag.shader");
	Shader circularwaveanimatedshader = Shader("vertex.shader", "circularwaveanimatedfrag.shader");
	Shader marblepatternshader = Shader("vertex.shader", "marblepatternfrag.shader");
	Shader noisepatternshader = Shader("vertex.shader", "noisepatternfrag.shader");
	Shader radialgradientshader = Shader("vertex.shader", "radialgradientfrag.shader");
	Shader stripspatternshader = Shader("vertex.shader", "stripspatternfrag.shader");
	Shader woodgrainpatternshader = Shader("vertex.shader", "woodgrainpatternfrag.shader");

	Shader shaders[] = {
		checkerboardshader,
		checkerboardwithcirculargradientshader,
		circularwaveanimatedshader,
		marblepatternshader,
		noisepatternshader,
		radialgradientshader,
		stripspatternshader,
		woodgrainpatternshader
	};

	//RENDER LOOP
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		if (captureMouse)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		ProcessInputs(window);
		camera.ProcessKeyboard(cameraDirection, deltaTime);

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (draw)
		{
			// can send one shader that is shaders[Selecteditem] instead of sending the whole array.
			ChangeFragShader(shaders[Selecteditem], Selecteditem, color1, color2, mul);
		}

		ImGui::Begin("Properties");
		ImGui::Text("Set the properties of the rendered objects.");
		ImGui::Checkbox("Draw Objects", &draw);
		ImGui::Combo("Texture Type", &Selecteditem, items, IM_ARRAYSIZE(items));
		if (needColors)
		{
			ImGui::ColorEdit4("Color 1", color1);
			ImGui::ColorEdit4("Color 2", color2);
		}
		if (needDistance)
		{
			ImGui::SliderFloat("Distance", &mul, 0.0f, 2.0f);
		}
		ImGui::End();

		cout << cameraDirection << endl;
		//myShader.setMat4("view", view);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	DeleteCubeData();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}

float ConvertToRGB(float val)
{
	return (val / 255.0f);
}

void ProcessInputs(GLFWwindow* window)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
		captureMouse = true;
	else
		captureMouse = false;


	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (captureMouse)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraDirection = Camera_Movement::FORWARD;
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraDirection = Camera_Movement::BACKWARD;
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraDirection = Camera_Movement::LEFT;
		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraDirection = Camera_Movement::RIGHT;
		else
			cameraDirection = Camera_Movement::NONE;
	}
	else
	{
		cameraDirection = Camera_Movement::NONE;
	}
}

void ChangeFragShader(Shader shader, int selectedItem, float color1[4], float color2[4], float mul)
{
	switch (selectedItem)
	{
		case 0: RenderCube(shader, color1, color2, mul, resolution, camera);
			needColors = true;
			needDistance = false;
			break;
		case 1: RenderCube(shader, color1, color2, mul, resolution, camera);
			needColors = true;
			needDistance = false;
			break;
		case 2: RenderCube(shader, color1, color2, mul, resolution, camera);
			needColors = true;
			needDistance = false;
			break;
		case 3: RenderCube(shader, color1, color2, mul, resolution, camera);
			needColors = true;
			needDistance = false;
			break;
		case 4: RenderCube(shader, color1, color2, mul, resolution, camera);
			needColors = false;
			needDistance = false;
			break;
		case 5: RenderCube(shader, color1, color2, mul, resolution, camera);
			needColors = true;
			needDistance = true;
			break;
		case 6: RenderCube(shader, color1, color2, mul, resolution, camera);
			needColors = true;
			needDistance = false;
			break;
		case 7: RenderCube(shader, color1, color2, mul, resolution, camera);
			needColors = true;
			needDistance = false;
			break;
	}
}

void frameBufferSizeCallBack(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	/*resolution.x = width;
	resolution.y = height;*/
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (!captureMouse)
	{
		firstMouse = true;
		return;
	}

	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xoffset = xPos - lastX;
	float yoffset = lastY - yPos; // reversed since y-coordinates range from bottom to top
	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void ScrollCallback(GLFWwindow*, double xOffset, double yOffset)
{
	camera.ProcessMouseScroll(yOffset);
}
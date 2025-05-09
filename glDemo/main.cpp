
#include "core.h"
#include "TextureLoader.h"
#include "GUClock.h"
#include "shader_setup.h"
#include "helper.h"
#include "AIMesh.h"
#include "Scene.h"
#include "Model.h"



using namespace std;
using namespace glm;


#pragma region Global variables

GUClock* g_gameClock = nullptr;

// Mouse tracking
bool				g_mouseDown = false;
double				g_prevMouseX, g_prevMouseY;

//Global Game Object
Scene* g_Scene = nullptr;
// Window size
const unsigned int g_initWidth = 1024;
const unsigned int g_initHeight = 1024;

float windowHeight = 0;
float windowWidth = 0;
bool aDown = false;
bool dDown = false;
bool wDown = false;
bool sDown = false;

#pragma endregion


// Function prototypes
void renderScene();
void updateScene();
void resizeWindow(GLFWwindow* _window, int _width, int _height);
void keyboardHandler(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
void mouseMoveHandler(GLFWwindow* _window, double _xpos, double _ypos);
void mouseButtonHandler(GLFWwindow* _window, int _button, int _action, int _mods);
void mouseScrollHandler(GLFWwindow* _window, double _xoffset, double _yoffset);
void mouseEnterHandler(GLFWwindow* _window, int _entered);

void input(); // Function to handle input events
int main()
{
	//
	// 1. Initialisation
	//

	g_gameClock = new GUClock();

#pragma region OpenGL and window setup

	// Initialise glfw and setup window
	glfwInit();

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_TRUE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);

	GLFWwindow* window = glfwCreateWindow(g_initWidth, g_initHeight, "GDV5001", NULL, NULL);

	// Check window was created successfully
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	// Set callback functions to handle different events
	glfwSetFramebufferSizeCallback(window, resizeWindow); // resize window callback
	glfwSetKeyCallback(window, keyboardHandler); // Keyboard input callback
	glfwSetCursorPosCallback(window, mouseMoveHandler);
	glfwSetMouseButtonCallback(window, mouseButtonHandler);
	glfwSetScrollCallback(window, mouseScrollHandler);
	glfwSetCursorEnterCallback(window, mouseEnterHandler);

	// Initialise glew
	glewInit();


	// Setup window's initial size
	resizeWindow(window, g_initWidth, g_initHeight);

#pragma endregion

	// Initialise scene - geometry and shaders etc
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // setup background colour to be black
	glClearDepth(1.0f);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	//
	//Set up Scene class
	//

	g_Scene = new Scene();


	ifstream manifest;
	manifest.open("manifest.txt");

	g_Scene->Load(manifest);
	g_Scene->Init();

	manifest.close();


	//
	// Main loop
	// 

	while (!glfwWindowShouldClose(window))
	{
		updateScene();
		renderScene();						// Render into the current buffer
		glfwSwapBuffers(window);			// Displays what was just rendered (using double buffering).

		glfwPollEvents();					// Use this version when animating as fast as possible

		// update window title
		char timingString[256];
		sprintf_s(timingString, 256, "CIS5013: Average fps: %.0f; Average spf: %f", g_gameClock->averageFPS(), g_gameClock->averageSPF() / 1000.0f);
		glfwSetWindowTitle(window, timingString);
	}

	glfwTerminate();

	if (g_gameClock)
	{
		g_gameClock->stop();
		g_gameClock->reportTimingData();
	}

	return 0;
}


// renderScene - function to render the current scene
void renderScene()
{
	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#// Render principle axes - no modelling transforms so just use cameraTransform

		g_Scene->Render();
}


// Function called to animate elements in the scene
void updateScene() 
{
	float tDelta = 0.0f;
	input();

	if (g_gameClock) {

		g_gameClock->tick();
		tDelta = (float)g_gameClock->gameTimeDelta();
	}

	g_Scene->Update(tDelta,(windowWidth/windowHeight));
}


#pragma region Event handler functions
//none of this is currently passed to the Game object
//probably a good idea to do that

// Function to call when window resized
void resizeWindow(GLFWwindow* _window, int _width, int _height)
{

	glViewport(0, 0, _width, _height);		// Draw into entire window
	windowWidth = _width;
	windowHeight = _height;
}


// Function to call to handle keyboard input
void keyboardHandler(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
	

	if (_action == GLFW_PRESS) {

		// check which key was pressed...
		switch (_key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(_window, true);
			break;

		case GLFW_KEY_SPACE:
			g_Scene->Input();
			break;
		case GLFW_KEY_A:
			aDown = true;
			
			break;
		case GLFW_KEY_D:
			dDown = true;
			
			break;
		case GLFW_KEY_W:
			wDown = true;
			
			break;
		case GLFW_KEY_S:
			sDown = true;
			break;
		default:
		{
		}
		}
	}
	else if (_action == GLFW_RELEASE) 
	{
		// handle key release events
		switch (_key)
		{
		case GLFW_KEY_A:
			aDown = false;
			break;
		case GLFW_KEY_D:
			dDown = false;
			break;
		case GLFW_KEY_W:
			wDown = false;
			break;
		case GLFW_KEY_S:
			sDown = false;
			break;

		default:
		{
		}
		}
	}
}


void mouseMoveHandler(GLFWwindow* _window, double _xpos, double _ypos) 
{
	if (g_mouseDown) {

		//float tDelta = gameClock->gameTimeDelta();

		float dx = float(_xpos - g_prevMouseX);// *360.0f * tDelta;
		float dy = float(_ypos - g_prevMouseY);// *360.0f * tDelta;
		
		g_Scene->mouseMoveHandlerC(dy, dx);
		g_prevMouseX = _xpos;
		g_prevMouseY = _ypos;
	}
}

void mouseButtonHandler(GLFWwindow* _window, int _button, int _action, int _mods) 
{
	if (_button == GLFW_MOUSE_BUTTON_LEFT) 
	{
		if (_action == GLFW_PRESS) 
		{
			g_mouseDown = true;
			glfwGetCursorPos(_window, &g_prevMouseX, &g_prevMouseY);
		}
		else if (_action == GLFW_RELEASE) 
		{
			g_mouseDown = false;
		}
	}
}

void mouseScrollHandler(GLFWwindow* _window, double _xoffset, double _yoffset) 
{

	
		g_Scene->mouseScrollHandlerC(_xoffset, _yoffset);
	
}

void mouseEnterHandler(GLFWwindow* _window, int _entered) 
{
}

void input()
{
	if (aDown == true)
		g_Scene->CameraMovement(vec3(0, 0, 1), 0.001f);
	g_Scene->CameraMovementA(0.001f);
	if (dDown == true)
		g_Scene->CameraMovement(vec3(0, 0, -1), 0.001f);
	g_Scene->CameraMovementD(0.001f);
	if (wDown == true)
		g_Scene->CameraMovement(vec3(-1, 0, 0), 0.001f);
	g_Scene->CameraMovementW(0.001f);
	if (sDown == true)
		g_Scene->CameraMovement(vec3(1, 0, 0), 0.001f);
	    g_Scene->CameraMovementS(0.001f);
}
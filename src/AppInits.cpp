#include "App.hpp"


int App::initGLFW()
{
	if (!glfwInit())
		return printError("Failed to initialize GLFW");

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	_win = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, WIN_NAME, NULL, NULL);
	if (_win == NULL)
		return printError("Failed to open GLFW window");
	glfwMakeContextCurrent(_win);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(_win, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(_win, WIN_WIDTH/2, WIN_HEIGHT/2);

	// Set background color
	glClearColor(BG_COLOR);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
	return SUCCESS;
}


int App::initGLEW()
{
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK)
		return printError("Failed to initialize GLEW");
	return SUCCESS;
}


int App::initShaders()
{
	// Create and compile our GLSL program from the shaders
	_programID = LoadShaders(
		"./data/shaders/StandardShading.vertexshader",
		"./data/shaders/StandardShading.fragmentshader");
	return SUCCESS;
}


int App::initVertexArray()
{
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	return SUCCESS;
}


int App::initMatricesIDs()
{
	// Get a handle for our "MVP" uniform
	GLuint _matrixID = glGetUniformLocation(_programID, "MVP");
	GLuint _viewMatrixID = glGetUniformLocation(_programID, "V");
	GLuint _modelMatrixID = glGetUniformLocation(_programID, "M");
	return SUCCESS;
}

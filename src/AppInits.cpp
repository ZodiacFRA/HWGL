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
	_win = glfwCreateWindow(_winWidth, _winHeight, WIN_NAME, NULL, NULL);
	if (_win == NULL)
		return printError("Failed to open GLFW window");
	glfwMakeContextCurrent(_win);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(_win, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(_win, _winWidth/2, _winHeight/2);

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
	_programID = LoadShaders(VERTEX_SHADER, FRAGMENT_SHADER);
	return SUCCESS;
}


int App::initVertexArray()
{
	_vertexArrayID;
	glGenVertexArrays(1, &_vertexArrayID);
	glBindVertexArray(_vertexArrayID);
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


int App::initLights()
{
	// Get a handle for our "LightPosition" uniform
	glUseProgram(_programID);
	_lightID = glGetUniformLocation(_programID, "LightPosition_worldspace");
	return SUCCESS;
}


int App::initTexture()
{
	// Load the texture
	_texture = loadDDS("./data/objs/uvmap.DDS");
	// Get a handle for our "myTextureSampler" uniform
	_textureID  = glGetUniformLocation(_programID, "myTextureSampler");
	return SUCCESS;
}

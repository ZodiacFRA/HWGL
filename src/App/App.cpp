#include "App.hpp"


App::App()			// RIGHT / HEIGHT / FRONT
	: _winWidth(WIN_WIDTH), _winHeight(WIN_HEIGHT),
	_lastTime(glfwGetTime()), _nbFrames(0),
	_camPos(glm::vec3(0, 3, 5)), _hAngle(3.14f), // 3.14
	_vAngle(-0.5f), _lightPos(0, 5, 0)
{}

App::~App()
{
	for (auto it : _shaders) {
		if (it.second)
			delete it.second;
	}
	for (auto it : _objsLibrary) {
		if (it.second)
			delete it.second;
	}
	glDeleteVertexArrays(1, &_vertexArrayID);
	glfwTerminate();
}


int App::init() {
	int flag = SUCCESS;
	flag &= initGLFW();
	flag &= initGLEW();
	flag &= initVertexArray();
	flag &= initShaders();
	flag &= loadObjsLibrary();
	flag &= setupScene();

	// flag &= initLights();  // TODO move to scene tree
	return flag;
}


int App::setupScene()
{
	Obj *tmpObj = _objsLibrary["terrain"];
	// CHECK IF OBJ EXISTS
	Shader *tmpShader = _shaders["textured"];
	// CHECK IF SHADER EXISTS
	_sceneTree.insert("", "terrain", tmpObj, tmpShader);
	_sceneTree.insert("", "terrain2", tmpObj, tmpShader);
	_sceneTree.translateNode("terrain", glm::vec3(2, 0, 0));

	// tmpObj = _objsLibrary["suzanne"];
	// // CHECK IF OBJ EXISTS
	// tmpShader = _shaders["textured"];
	// // CHECK IF SHADER EXISTS
	// _sceneTree.insert("", "1stSuzanne", tmpObj, tmpShader);
	// _sceneTree.translateNode("1stSuzanne", glm::vec3(1, 0, 0));
	return SUCCESS;
}


int App::run()
{
	do {
		_currentTime = glfwGetTime();
		_nbFrames++;
		// If last prinf() was more than 1sec ago
		if (_currentTime - _lastTime >= 2.0) {
			printf("%f ms / frame\n", 2000.0 / double(_nbFrames));
			_nbFrames = 0;
			_lastTime += 2.0;
		}

		_lightPos = glm::vec3(rand() % 4 - 2, 0, 0);
		drawLights();

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Compute the MVP matrix from keyboard and mouse input
		if (!this->computeMatricesFromInputs())
			return FAILURE;

		_sceneTree.draw(_projectionMatrix, _viewMatrix);

		// Swap buffers
		glfwSwapBuffers(_win);
		glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(_win, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		!glfwWindowShouldClose(_win));
	return SUCCESS;
}


int App::drawLights()
{
	glUniform3f(_lightID, _lightPos.x, _lightPos.y, _lightPos.z);
	return SUCCESS;
}


int App::handleAspectRatio()
{
	// Handles window resize, I successfully change the aspectRatio
	// but not the window limits, even when calling glfwSetWindowSizeLimits
	static int oldWinWidth = _winWidth;
	static int oldWinHeight = _winHeight;
	// Check if window as been resized
	glfwGetWindowSize(_win, &_winWidth, &_winHeight);
	if (_winWidth != oldWinWidth || _winHeight != oldWinHeight) {
		glfwSetWindowSizeLimits(_win, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE);
		glfwSetWindowAspectRatio(_win, GLFW_DONT_CARE, GLFW_DONT_CARE);
		oldWinWidth = _winWidth;
	}
	return SUCCESS;
}

#include "App.hpp"


App::App()			// RIGHT / HEIGHT / FRONT
	: _winWidth(WIN_WIDTH), _winHeight(WIN_HEIGHT),
	_camPos(glm::vec3(-2, 3, 10)), _hAngle(2.95f), // 3.14
	_vAngle(-0.3f), _lightPos(-1, 4, 2), _tmpObj("test")
{}

App::~App()
{
	for (auto it : _shaders) {
		if (it.second)
			delete it.second;
	}
	glDeleteVertexArrays(1, &_vertexArrayID);
	glfwTerminate();
}

App &App::get()
{
	static App app;
	return app;
}


int App::init() {
	int flag = SUCCESS;
	flag &= initGLFW();
	flag &= initGLEW();
	flag &= initVertexArray();
	flag &= initShaders();

	_tmpObj.loadObj("./data/objs/cubeUV.obj");
	_tmpObj.setShader(_shaders["basicShader"]);

	flag &= initLights();  // TODO move to scene tree
	return flag;
}


int App::run()
{
	do {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// for _tmpObj in objects:
		// Compute the MVP matrix from keyboard and mouse input
		if (!this->computeMatricesFromInputs())
			return FAILURE;

		// drawLights();
		_tmpObj.draw(_projectionMatrix, _viewMatrix);

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

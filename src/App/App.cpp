#include "App.hpp"


App::App()			// RIGHT / HEIGHT / FRONT
	: _winWidth(WIN_WIDTH), _winHeight(WIN_HEIGHT), _hAngle(2.95f), // 3.14
	_vAngle(-0.3f), _camPos(glm::vec3(-2, 3, 10)),
	_lightPos(-1, 4, 2)
{}

App::~App()
{
	glDeleteProgram(_programID);
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
	flag &= initMatricesIDs();
	flag &= initTexture();
	_tmpObj.loadObj("./data/objs/cubeUV.obj");
	flag &= initLights();  // TODO move to scene tree
	return flag;
}


int App::run()
{
	do {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Use our shader
		glUseProgram(_programID);

		drawObjects();

		// Swap buffers
		glfwSwapBuffers(_win);
		glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(_win, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		!glfwWindowShouldClose(_win));
	return SUCCESS;
}


int App::drawObjects()
{
	// Compute the MVP matrix from keyboard and mouse input
	if (!this->computeMatricesFromInputs())
		return FAILURE;
	glm::mat4 ModelMatrix = glm::mat4(1.0);
	glm::mat4 MVP = _projectionMatrix * _viewMatrix * ModelMatrix;

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(_matrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(_modelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(_viewMatrixID, 1, GL_FALSE, &_viewMatrix[0][0]);

	drawLights();
	handleTexture();

	_tmpObj.draw();
	return SUCCESS;
}


int App::drawLights()
{
	glUniform3f(_lightID, _lightPos.x, _lightPos.y, _lightPos.z);
	return SUCCESS;
}


int App::handleTexture()
{
	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(_textureID, 0);
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

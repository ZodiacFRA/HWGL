#include "App.hpp"


App::App()
	: _hAngle(3.14f), _vAngle(0.0f), _camPos(glm::vec3( 0, 0, 5 )),
	_lightPos(glm::vec3(4,4,4))
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
	flag &= initShaders();
	flag &= initVertexArray();
	flag &= initMatricesIDs();
	flag &= initLights();  // TODO move to scene tree
	_tmpObj.load("./data/objs/icosphere.obj");
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
		drawLights();

		// Swap buffers
		glfwSwapBuffers(_win);
		glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(_win, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(_win) == 0 );
	return SUCCESS;
}


int App::drawObjects()
{
	// Compute the MVP matrix from keyboard and mouse input
	if (!computeMatricesFromInputs())
		return FAILURE;
	glm::mat4 ModelMatrix = glm::mat4(1.0);
	glm::mat4 MVP = _projectionMatrix * _viewMatrix * ModelMatrix;

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(_matrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(_modelMatrixID, 1, GL_FALSE, &_viewMatrix[0][0]);
	glUniformMatrix4fv(_viewMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	_tmpObj.draw();
	return SUCCESS;
}


int App::drawLights()
{
	glUniform3f(_lightID, _lightPos.x, _lightPos.y, _lightPos.z);
	return SUCCESS;
}

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


int App::setupScene()
{
	// Node name, Obj name, Shader name, Texture name, Position
	createNode("", "suzanneNode", "suzanneMe", "StandardShading",
		"suzUvPaint", glm::vec3(0, 0, 0));

	//
	// tmpShader = _shaders["colored"];
	// _sceneTree.insert("", "terrain2", tmpObj, tmpShader, tmpTexture);
	// _sceneTree.translateNode("terrain2", glm::vec3(1, 0, 0));

	// tmpObj = _objsLibrary["suzanne"];
	// CHECK IF OBJ EXISTS
	// tmpShader = _shaders["StandardShading"];
	// CHECK IF SHADER EXISTS
	// _sceneTree.insert("", "1stSuzanne", tmpObj, tmpShader);
	// _sceneTree.translateNode("1stSuzanne", glm::vec3(1, 0, 0));
	return SUCCESS;
}


int App::run()
{
	do {
		handleTime();

		// drawLights();

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_sceneTree.rotateNode("suzanneNode", 1.0, glm::vec3(0, 1, 0));
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

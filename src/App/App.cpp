#include "App.hpp"


App::App()			// RIGHT / HEIGHT / FRONT
	: _winWidth(WIN_WIDTH), _winHeight(WIN_HEIGHT),
	_lastTime(glfwGetTime()), _nbFrames(0),
	_camPos(glm::vec3(0, 3, 5)), _hAngle(3.14f), // 3.14
	_vAngle(-0.5f)
{}


int App::setupScene()
{
	// Node name, Obj name, Shader name, Texture name, Position
	// 1 openGL unit = 1m in Blender
	//
	createNode("", "suzanneNode", "suzanneMe", "StandardShading",
		"suzUvPaint", glm::vec3(0, 1, 0));

	// std::cout << glm::to_string(_sceneTree.getNode("suzanneNode")->modelMatrix) << '\n';
	// _sceneTree.setNodeRotation("suzanneNode", 90.0, glm::vec3(0, 0, 0));
	// std::cout << glm::to_string(_sceneTree.getNode("suzanneNode")->modelMatrix) << '\n';

	// glm::mat4 test(0.1);
	// std::cout << glm::to_string(test) << '\n';

	createNode("", "terrainNode", "plane", "StandardShadingNoSpec",
		"floortexture", glm::vec3(0, 0, 0));
	return SUCCESS;
}


int App::run()
{
	do {
		handleTime();
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// drawLights();

		// Change objs properties here
		// _sceneTree.setNodeScale("suzanneNode", glm::vec3(2.0, 1, 1.0));
		_sceneTree.rotateNode("suzanneNode", 1, glm::vec3(1, 0, 1));

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
	for (auto it : _textureLibrary) {
		if (it.second)
			delete it.second;
	}
	glDeleteVertexArrays(1, &_vertexArrayID);
	glfwTerminate();
}

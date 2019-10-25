#include "App.hpp"


App::App()			// RIGHT / HEIGHT / FRONT
	: _winWidth(WIN_WIDTH), _winHeight(WIN_HEIGHT),
	_lastTime(glfwGetTime()), _nbFrames(0),
	_camPos(glm::vec3(50, 50, 50)),
	_hAngle(glm::radians(-135.0)), _vAngle(-0.6)
{}


int App::setupScene()
{
	// Node name, Obj name, Shader name, Texture name, Position
	// 1 openGL unit = 1m in Blender

	// createNode("", "suzanneNode", "suzanneMe", "StandardShading",
	// 	"suzUvPaint", glm::vec3(0, 1, 0));

	createNode("", "axisNode", "axis", "StandardShading",
		"", glm::vec3(0, 1, 0));
	_sceneTree.scaleNode("axisNode", glm::vec3(0.4, 0.4, 0.4));

	createNode("", "terrain1Node", "rectFloor", "StandardShadingNoSpec",
		"floortexture", glm::vec3(0, 0, 0));
	createNode("", "terrain2Node", "rectFloor", "StandardShadingNoSpec",
		"floortexture", glm::vec3(0, 0, 0));
	_sceneTree.translateNode("terrain2Node", glm::vec3(0, 0, -12));
	createNode("", "terrain3Node", "rectFloor", "StandardShadingNoSpec",
		"floortexture", glm::vec3(0, 0, 0));
	_sceneTree.translateNode("terrain3Node", glm::vec3(0, 0, 12));

	return SUCCESS;
}


int App::run()
{
	do {
		handleTime();
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Change objs properties here

		// Compute the MVP matrix from keyboard and mouse input
		if (!this->computeMatricesFromInputs(true, 10.0f, true))
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

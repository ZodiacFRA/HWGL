#include "App.hpp"


App::App()
	: _winWidth(WIN_WIDTH), _winHeight(WIN_HEIGHT),  // store win size to handle resize
	_lastTime(glfwGetTime()), _nbFrames(0),  // speed handling
	// Only 2 decimals allowed on worldspeed, multiple of 2
	_worldSpeed(0.25), _distMoved(0.0),
	_camPos(glm::vec3(0, 15, 10)),  // RIGHT / HEIGHT / FRONT
	_hAngle(glm::radians(-180.0)), _vAngle(-0.8),  // camera lookat
	_jumpStart(0.0), _lives(5), _score(0), _shake(false)  // Game parameters
{}


int App::setupScene()
{
	// Node name, Obj name, Shader name, Texture name, Position
	// 1 openGL unit = 1m in Blender

	_playerNode = createNode("", "PlayerNode", "Player", "StandardShading",
		"Player", glm::vec3(0, 0, 0));

	createNode("", "terrainLeftNode", "rectFloor", "StandardShading",
		"floortexture", glm::vec3(0, 0, 0));
	createNode("", "terrainMidNode", "rectFloor", "StandardShading",
		"floortexture", glm::vec3(0, 0, PROP_SPAWN));
	createNode("", "terrainRightNode", "rectFloor", "StandardShading",
		"floortexture", glm::vec3(0, 0, 2 * PROP_SPAWN));
	return SUCCESS;
}


int App::run()
{
	sf::Music music;
	if (!music.openFromFile("./data/sounds/music.wav"))
		return FAILURE;
	if (true)
		music.play();
	do {
		if (handleTime()) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			moveScenery();  // Handle scenery scrolling
			handlePlayerMovement();

			// if (!this->computeMatricesFromInputs(true, 100.0f, true))
			if (!this->computeMatricesFromInputs(true, 40.0f, false))
				return FAILURE;

			_sceneTree.draw(_projectionMatrix, _viewMatrix);

			// Draw info text
			char text[256];
			sprintf(text,"Score:%d Lives:%d", _score, _lives);
			printText2D(text, 0, 570, 20);

			// Swap buffers
			glfwSwapBuffers(_win);
			glfwPollEvents();
		}
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(_win, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		!glfwWindowShouldClose(_win));
	return SUCCESS;
}


App::~App()
{
	// Properly delete all assets libraries
	for (auto it : _shadersLibrary) {
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
	// Properly delete all GL attributes and buffers
	glDeleteVertexArrays(1, &_vertexArrayID);
	cleanupText2D();
	glfwTerminate();
}

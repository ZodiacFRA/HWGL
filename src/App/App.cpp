#include "App.hpp"


App::App()			// RIGHT / HEIGHT / FRONT
	: _winWidth(WIN_WIDTH), _winHeight(WIN_HEIGHT),
	_lastTime(glfwGetTime()), _nbFrames(0),
	// Only 2 decimals allowed on worldspeed, multiple of 2
	_worldSpeed(0.25), _distMoved(0.0),
	// _camPos(glm::vec3(200, 200, 200)),
	_camPos(glm::vec3(0, 15, 10)),
	_hAngle(glm::radians(-180.0)), _vAngle(-0.8),
	_jumpStart(0.0), _lives(3), _score(0), _shake(false)
{}


int App::setupScene()
{
	// Node name, Obj name, Shader name, Texture name, Position
	// 1 openGL unit = 1m in Blender

	_playerNode = createNode("", "PlayerNode", "Player", "StandardShading",
		"Player", glm::vec3(0, 0, 0));

	createNode("", "terrainLeftNode", "rectFloor", "StandardShadingNoSpec",
		"floortexture", glm::vec3(0, 0, 0));
	createNode("", "terrainMidNode", "rectFloor", "StandardShadingNoSpec",
		"floortexture", glm::vec3(0, 0, PROP_SPAWN));
	createNode("", "terrainRightNode", "rectFloor", "StandardShadingNoSpec",
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
		handleTime();
		// if (static_cast<int>(std::round(_distMoved)) % 1000 == 0) {
		// 	_worldSpeed += 0.2;
		// 	std::cout << "BUFF" << '\n';
		// }
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Change objs properties here
		moveScenery();
		handlePlayerMovement();

		// if (!this->computeMatricesFromInputs(true, 2.0f, true))
		if (!this->computeMatricesFromInputs(true, 40.0f, false))
			return FAILURE;

		_sceneTree.draw(_projectionMatrix, _viewMatrix);

		// Draw Text
		char text[256];
		// sprintf(text,"Je suis con");
		sprintf(text,"Score:%d Lives:%d", _score, _lives);
		printText2D(text, 0, 570, 20);

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
	glDeleteVertexArrays(1, &_vertexArrayID);
	cleanupText2D();
	glfwTerminate();
}

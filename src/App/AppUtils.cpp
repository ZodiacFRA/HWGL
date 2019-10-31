#include "App.hpp"


int App::handleCollision(Node *Node)
{
	glm::vec3 objPos = Node->modelMatrix[3];
	glm::vec3 playerPos = _playerNode->modelMatrix[3];
	float hitboxSize = 1.2;
	if (objPos[2] > -1 * hitboxSize && objPos[2] < hitboxSize &&
		objPos[0] > playerPos[0] - hitboxSize && objPos[0] < playerPos[0] + hitboxSize &&
		objPos[1] > playerPos[1]) {
		return SUCCESS;
	}
	return FAILURE;
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


void App::handleTime()
{
	_currentTime = glfwGetTime();
	_deltaTime = _currentTime - _lastTime;
	_lastTime = _currentTime;

	// FPS counter
	_nbFrames++;
	static float lastFrameTime = glfwGetTime();
	if (_currentTime - lastFrameTime >= 0.1) {
		_fps = float(_nbFrames) / (_currentTime - lastFrameTime);
		_nbFrames = 0;
		lastFrameTime = _currentTime;
	}
}

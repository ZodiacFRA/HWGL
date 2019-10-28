#include "App.hpp"


int App::handlePlayerMovement()
{
	bool jumpFlag = glfwGetKey(_win, GLFW_KEY_SPACE) == GLFW_PRESS;
	if (_playerNode->modelMatrix[3][1] < 0.1) {  // Can jump
		_sceneTree.setNodePosition("PlayerNode",
			glm::vec3(0, 0, 0));
		if (jumpFlag) {
			_jumpStart = _currentTime;
			_sceneTree.setNodePosition("PlayerNode",
				glm::vec3(0, 0.1, 0));
		}
	} else {  // In a jump
		float deltaT = _currentTime - _jumpStart;
		float height = 2 * sin(14 * deltaT + ((3.3 * PI) / 2)) + 2;
		_sceneTree.setNodePosition("PlayerNode",
				glm::vec3(0, height, 0));
	}
	return SUCCESS;
}

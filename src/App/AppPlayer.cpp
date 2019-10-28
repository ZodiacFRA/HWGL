#include "App.hpp"


int App::handlePlayerMovement()
{
	handleJump();
	handleMove();
	// -1 / (1 + exp(x - 4)) + 1

	return SUCCESS;
}


int App::handleMove()
{
	static int moveDirection = 0;  // -1 = left, 0 = None, 1 = right
	glm::vec3 playerPosMatrix = _playerNode->modelMatrix[3];

	if (glfwGetKey(_win, GLFW_KEY_LEFT) == GLFW_PRESS)
		moveDirection = -1;
	else if (glfwGetKey(_win, GLFW_KEY_RIGHT) == GLFW_PRESS)
		moveDirection = 1;
	else if (playerPosMatrix[0] == -2.0 || playerPosMatrix[0] == 2.0 ||
		(playerPosMatrix[0] >= -0.1 && playerPosMatrix[0] <= 0.1))
		moveDirection = 0;
	if (moveDirection == -1 && playerPosMatrix[0] >= -2.0) {
		_sceneTree.translateNode("PlayerNode",
				glm::vec3(-0.2, 0, 0));
	} else if (moveDirection == 1 && playerPosMatrix[0] <= 2.0) {
			_sceneTree.translateNode("PlayerNode",
					glm::vec3(0.2, 0, 0));
	}


	return SUCCESS;
}


int App::handleJump()
{
	glm::vec3 playerPosMatrix = _playerNode->modelMatrix[3];

	bool jumpFlag = glfwGetKey(_win, GLFW_KEY_SPACE) == GLFW_PRESS;
	if (playerPosMatrix[1] < 0.1) {  // Can jump
		if (jumpFlag) {
			_jumpStart = _currentTime;
			_sceneTree.setNodePosition("PlayerNode",
				glm::vec3(playerPosMatrix[0], 0.1, 0));
		}
	} else {  // In a jump
		float deltaT = _currentTime - _jumpStart;
		float height = 2 * sin(10 * deltaT + ((3.3 * PI) / 2)) + 2;
		_sceneTree.setNodePosition("PlayerNode",
				glm::vec3(playerPosMatrix[0], height, 0));
	}
	return SUCCESS;
}

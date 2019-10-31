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
	// Gotta figure how to prevent double move
	static int moveDirection = 0;  // -1 = left, 0 = None, 1 = right
	glm::vec3 playerPosMatrix = _playerNode->modelMatrix[3];

	bool goLeft = glfwGetKey(_win, GLFW_KEY_LEFT) == GLFW_PRESS;
	bool goRight = glfwGetKey(_win, GLFW_KEY_RIGHT) == GLFW_PRESS;
	static bool hasReleasedLeft = true;
	static bool hasReleasedRight = true;
	hasReleasedLeft |= glfwGetKey(_win, GLFW_KEY_LEFT) == GLFW_RELEASE;
	hasReleasedRight |= glfwGetKey(_win, GLFW_KEY_RIGHT) == GLFW_RELEASE;
	// if (hasReleasedLeft)
	// 	goLeft = false;
	// if (hasReleasedRight)
	// 	goRight = false;

	// std::cout << "-------------" << '\n';
	// std::cout << goLeft << goRight << '\n';
	// std::cout << hasReleasedLeft << hasReleasedRight << '\n';

	if (goLeft && hasReleasedLeft && playerPosMatrix[0] != -2.0) {
		// playSound("move");
		moveDirection = -1;
		hasReleasedLeft = false;
	} else if (goRight && hasReleasedRight && playerPosMatrix[0] != 2.0) {
		moveDirection = 1;
		hasReleasedRight = false;
		// playSound("move");
	} else if (playerPosMatrix[0] == -2.0 || playerPosMatrix[0] == 2.0 ||
		(playerPosMatrix[0] >= -0.1 && playerPosMatrix[0] <= 0.1)) {
		moveDirection = 0;
	}
	if (moveDirection == -1 && playerPosMatrix[0] > -1.9) {
		_sceneTree.translateNode("PlayerNode",
				glm::vec3(-0.4, 0, 0));
	} else if (moveDirection == 1 && playerPosMatrix[0] <= 1.9) {
			_sceneTree.translateNode("PlayerNode",
					glm::vec3(0.4, 0, 0));
	}
	_camPos = glm::vec3(-playerPosMatrix[0] / 7, 15 + playerPosMatrix[1], 10);
	return SUCCESS;
}


int App::handleJump()
{
	glm::vec3 playerPosMatrix = _playerNode->modelMatrix[3];

	bool jumpFlag = glfwGetKey(_win, GLFW_KEY_SPACE) == GLFW_PRESS;
	if (playerPosMatrix[1] < 0.1) {  // Can jump
		if (jumpFlag) {
			playSound("jump");
			_jumpStart = _currentTime;
			_sceneTree.setNodePosition("PlayerNode",
				glm::vec3(playerPosMatrix[0], 0.1, 0));
		}
	} else {  // In a jump
		float deltaT = _currentTime - _jumpStart;
		float height = 1.5 * sin(12 * deltaT + ((3.3 * PI) / 2)) + 1.5;
		_sceneTree.setNodePosition("PlayerNode",
				glm::vec3(playerPosMatrix[0], height, 0));
	}
	return SUCCESS;
}

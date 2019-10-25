#include "App.hpp"


int App::moveFloor(float speed)
{
	Node *left = _sceneTree.getNode("terrainLeftNode");
	Node *mid = _sceneTree.getNode("terrainMidNode");
	Node *right = _sceneTree.getNode("terrainRightNode");
	if (mid->modelMatrix[3][2] > 12) {
		glm::vec3 tM(0, 0, -12);
		left->modelMatrix = glm::translate(left->modelMatrix, tM);
		mid->modelMatrix = glm::translate(mid->modelMatrix, tM);
		right->modelMatrix = glm::translate(right->modelMatrix, tM);
	} else {
		glm::vec3 tM(0, 0, speed);
		left->modelMatrix = glm::translate(left->modelMatrix, tM);
		mid->modelMatrix = glm::translate(mid->modelMatrix, tM);
		right->modelMatrix = glm::translate(right->modelMatrix, tM);
	}
	return SUCCESS;
}

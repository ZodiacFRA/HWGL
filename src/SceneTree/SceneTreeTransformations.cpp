#include "SceneTree.hpp"


int SceneTree::translateNode(std::string nodeName, glm::vec3 tM)
{
	Node *node = _nodes[nodeName];
	node->modelMatrix = glm::translate(node->modelMatrix, tM);
	return SUCCESS;
}


int SceneTree::setNodePosition(std::string nodeName, glm::vec3 pM)
{
	Node *node = _nodes[nodeName];
	glm::vec3 mM = node->modelMatrix[3];
	glm::vec3 tM(pM[0] - mM[0], pM[1] - mM[1], pM[2] - mM[2]);
	node->modelMatrix = glm::translate(node->modelMatrix, tM);
	return SUCCESS;
}


int SceneTree::rotateNode(std::string nodeName, float degrees, glm::vec3 rM)
{
	Node *node = _nodes[nodeName];
	// x, y, z are the axis of rotation
	node->modelMatrix = glm::rotate(node->modelMatrix,
					glm::radians(degrees), rM);
	return SUCCESS;
}

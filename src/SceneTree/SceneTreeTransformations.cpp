#include "SceneTree.hpp"


int SceneTree::translateNode(std::string nodeName, glm::vec3 tM)
{
	Node *node = NULL;
	auto it = _nodes.find(nodeName);
	if (it != _nodes.end())
		node = it->second;
	else
		return printError("Can't translate node (Node not found)");
	node->modelMatrix = glm::translate(node->modelMatrix, tM);
	return SUCCESS;
}

int SceneTree::setNodePosition(std::string nodeName, glm::vec3 pM)
{
	Node *node = NULL;
	auto it = _nodes.find(nodeName);
	if (it != _nodes.end())
		node = it->second;
	else
		return printError("Can't set Node position (Node not found)");
	glm::vec3 mM = node->modelMatrix[3];
	glm::vec3 tM(pM[0] - mM[0], pM[1] - mM[1], pM[2] - mM[2]);
	node->modelMatrix = glm::translate(node->modelMatrix, tM);
	return SUCCESS;
}

int SceneTree::rotateNode(std::string nodeName, float degrees, glm::vec3 rM)
{
	Node *node = NULL;
	auto it = _nodes.find(nodeName);
	if (it != _nodes.end())
		node = it->second;
	else
		return printError("Can't rotate node (Node not found)");
	// x, y, z are the axis of rotation
	node->modelMatrix = glm::rotate(node->modelMatrix,
					glm::radians(degrees), rM);
	return SUCCESS;
}

int SceneTree::setNodeRotation(std::string nodeName, float degrees, glm::vec3 rM)
{
	// DOES NOT WORK
	Node *node = NULL;
	auto it = _nodes.find(nodeName);
	if (it != _nodes.end())
		node = it->second;
	else
		return printError("Can't set node rotation (Node not found)");
	glm::vec3 mM = node->modelMatrix[3];
	glm::vec3 resM(rM[0] - mM[0], rM[1] - mM[1], rM[2] - mM[2]);
	node->modelMatrix = glm::rotate(node->modelMatrix,
					glm::radians(degrees), resM);
	return SUCCESS;
}

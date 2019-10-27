#include "App.hpp"


int App::moveFloor()
{
	Node *left = _sceneTree.getNode("terrainLeftNode");
	Node *mid = _sceneTree.getNode("terrainMidNode");
	Node *right = _sceneTree.getNode("terrainRightNode");
	glm::vec3 worldMovmentM(0, 0, _worldSpeed);

	if (mid->modelMatrix[3][2] > 12) {
		glm::vec3 tM(0, 0, -12);
		left->modelMatrix = glm::translate(left->modelMatrix, tM);
		mid->modelMatrix = glm::translate(mid->modelMatrix, tM);
		right->modelMatrix = glm::translate(right->modelMatrix, tM);
	} else {
		left->modelMatrix = glm::translate(left->modelMatrix, worldMovmentM);
		mid->modelMatrix = glm::translate(mid->modelMatrix, worldMovmentM);
		right->modelMatrix = glm::translate(right->modelMatrix, worldMovmentM);
	}
	
	std::vector<std::string> toDelete;
	for (auto it : _sceneryNodes) {
		glm::mat4 mM = it.second->modelMatrix;
		if (mM[3][2] > 12) {  // If out of screen
			_sceneTree.remove(it.first);
			// Remove from _sceneryNodes as well
			toDelete.push_back(it.first);
		} else {  // Keep moving
			it.second->modelMatrix = glm::translate(mM, worldMovmentM);
		}
	}
	for (auto it : toDelete)
		_sceneryNodes.erase(it);

	_distMoved += _worldSpeed;
	int tmpDist = static_cast<int>(std::round(_distMoved * 10));
	if (tmpDist % 10 == 0) {
		std::string tmpName(std::to_string(_distMoved));
		Node *tmp;
		int tmpRand = rand() % 10;
		if (tmpRand >= 5) {  // Back
			tmp = createNode("", tmpName, "cube",
			"StandardShadingNoSpec", "cube",
			glm::vec3(2, 1, -24));
			_sceneryNodes.emplace(tmpName, tmp);
		} else if (tmpRand <= 5) {
			tmp = createNode("", tmpName, "cube",
			"StandardShadingNoSpec", "cube",
			glm::vec3(-2, 1, -24));
			_sceneryNodes.emplace(tmpName, tmp);
		}
	}
	return SUCCESS;
}

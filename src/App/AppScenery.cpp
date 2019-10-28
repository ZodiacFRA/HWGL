#include "App.hpp"


int App::moveScenery()
{
	glm::vec3 worldMovmentM(0, 0, _worldSpeed);
	moveFloor(worldMovmentM);
	moveProps(worldMovmentM);

	_distMoved += _worldSpeed;
	static float lastAddDistance = 0.0;
	// Workaround needed to get a modulo of a float number
	// fmod does not work as it returns too many decimals
	// So I just * 100 then % 200 the distance moved
	// I also use the lastAddDistance rather than the real distance
	// to prevent any overflow
	int tmpDist = static_cast<int>(std::round((_distMoved - lastAddDistance) * 100));
	if (tmpDist % 200 == 0) {
		addProps();
		lastAddDistance = _distMoved;
	}

	return SUCCESS;
}


int App::addProps()
{
	std::string name(std::to_string(_distMoved));
	int tmpRand = rand() % 10;
	if (tmpRand >= 5) {  // Back
		createRandomProp(name, 2, tmpRand % 5);
	} else if (tmpRand <= 4) {  // Front
		createRandomProp(name, -2, tmpRand % 5);
	}
	return SUCCESS;
}


int App::createRandomProp(std::string name, int x, int rand)
{
	Node *tmp;
	std::string objType;
	if (rand == 0)
		objType = "obs0";
	if (rand == 1)
		objType = "obs1";
	if (rand == 2)
		objType = "obs2";
	if (rand == 3)
		objType = "obs3";
	if (rand == 4)
		objType = "obs4";

	tmp = createNode("", name, objType,
	"StandardShadingNoSpec", "cube",
	glm::vec3(x, 0, -24));
	_sceneryNodes.emplace(name, tmp);
	return SUCCESS;
}


int App::moveFloor(glm::vec3 worldM)
{
	Node *left = _sceneTree.getNode("terrainLeftNode");
	Node *mid = _sceneTree.getNode("terrainMidNode");
	Node *right = _sceneTree.getNode("terrainRightNode");

	if (mid->modelMatrix[3][2] >= 12) {
		glm::vec3 tM(0, 0, -12);
		left->modelMatrix = glm::translate(left->modelMatrix, tM);
		mid->modelMatrix = glm::translate(mid->modelMatrix, tM);
		right->modelMatrix = glm::translate(right->modelMatrix, tM);
	} else {
		left->modelMatrix = glm::translate(left->modelMatrix, worldM);
		mid->modelMatrix = glm::translate(mid->modelMatrix, worldM);
		right->modelMatrix = glm::translate(right->modelMatrix, worldM);
	}
	return SUCCESS;
}


int App::moveProps(glm::vec3 worldM)
{
	std::vector<std::string> toDelete;
	for (auto it : _sceneryNodes) {
		glm::mat4 mM = it.second->modelMatrix;
		if (mM[3][2] > 12) {  // If out of screen
			_sceneTree.remove(it.first);
			// Remove from _sceneryNodes as well
			toDelete.push_back(it.first);
		} else {  // Keep moving
			it.second->modelMatrix = glm::translate(mM, worldM);
		}
	}
	for (auto it : toDelete)
		_sceneryNodes.erase(it);
	return SUCCESS;
}

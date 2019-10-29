#include "App.hpp"


int App::moveScenery()
{
	glm::vec3 worldMovmentM(0, 0, _worldSpeed);
	moveFloor(worldMovmentM);
	moveObjects(worldMovmentM);

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
		addBorders();
		lastAddDistance = _distMoved;
	}
	return SUCCESS;
}


int App::addProps()
{
	int tmpRand = rand() % 10;
	std::string name(std::to_string(_distMoved));

	if (tmpRand < 3)
		createRandomProp(name.append("0"), 2);
	if (tmpRand > 1 && tmpRand < 5)  // Front
		createRandomProp(name.append("1"), -2);
	if (tmpRand > 4 && tmpRand < 8)
	       createRandomProp(name.append("2"), 0);
	return SUCCESS;
}


int App::createRandomProp(std::string name, int x)
{
	Node *tmp;
	std::string objType;
	int tmpRand = rand() % 100;
	if (tmpRand < 60)
		objType = "point";
	else if (tmpRand < 90)
		objType = "malus";
	else if (tmpRand < 100)
		objType = "bonus";

	tmp = createNode("", name, objType,
	"StandardShadingNoSpec", "dev",
	glm::vec3(x, 0, 2 * PROP_SPAWN));
	_sceneryNodes.emplace(name, tmp);
	return SUCCESS;
}


int App::addBorders()
{
	int tmpRand = rand() % 10;
	std::string name(std::to_string(_distMoved));
	createRandomBorder(name.append("L"), 4, tmpRand % 5);
	createRandomBorder(name.append("R"), -4, tmpRand % 5);
	return SUCCESS;
}


int App::createRandomBorder(std::string name, int x, int rand)
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
	"StandardShadingNoSpec", "dev",
	glm::vec3(x, 0, 2 * PROP_SPAWN));
	_sceneryNodes.emplace(name, tmp);
	return SUCCESS;
}


int App::moveFloor(glm::vec3 worldM)
{
	Node *left = _sceneTree.getNode("terrainLeftNode");
	Node *mid = _sceneTree.getNode("terrainMidNode");
	Node *right = _sceneTree.getNode("terrainRightNode");

	if (left->modelMatrix[3][2] > 23.8) {  // reset pos
		_sceneTree.setNodePosition("terrainLeftNode", glm::vec3(0, 0, 0));
		_sceneTree.setNodePosition("terrainMidNode", glm::vec3(0, 0, PROP_SPAWN));
		_sceneTree.setNodePosition("terrainRightNode", glm::vec3(0, 0, 2 * PROP_SPAWN));
	} else {
		left->modelMatrix = glm::translate(left->modelMatrix, worldM);
		mid->modelMatrix = glm::translate(mid->modelMatrix, worldM);
		right->modelMatrix = glm::translate(right->modelMatrix, worldM);
	}
	return SUCCESS;
}


int App::moveObjects(glm::vec3 worldM)
{
	std::vector<std::string> toDelete;
	for (auto it : _sceneryNodes) {
		glm::mat4 mM = it.second->modelMatrix;
		if (mM[3][2] > PROP_END) {  // If out of screen
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

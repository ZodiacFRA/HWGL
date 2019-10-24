#include "SceneTree.hpp"


SceneTree::SceneTree()
{
	_root.name = "";
}

SceneTree::~SceneTree()
{
	for (auto it : _nodes) {
		if (it.second)
			delete it.second;
	}
}


int SceneTree::insert(std::string parentName, std::string name, Obj *obj,
			Shader *shader, Texture *texture, glm::vec3 position)
{
	if (_nodes.find(name) != _nodes.end())
		return printError("Node name already taken");
	Node *parentNode;
	if (parentName == "")  // TERNAIRE
		parentNode = &_root;
	else
		parentNode = _nodes[parentName];
	Node *newNode = new Node;
	newNode->name = name;
	newNode->modelMatrix = glm::translate(glm::mat4(1.0), position);
	newNode->parent = parentNode;
	newNode->obj = obj;
	newNode->shader = shader;
	newNode->texture = texture;
	parentNode->childs.push_back(newNode);
	_nodes.emplace(name, newNode);
	return SUCCESS;
}


int SceneTree::draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
	for (auto it : _nodes) {
		it.second->shader->setupDraw(projectionMatrix, viewMatrix,
					it.second->modelMatrix);
		// SHOULD ADD ALL PARENTS TRANSFORMATIONS AS WELL!
		if (it.second->texture)
			it.second->texture->setupDraw(
				it.second->shader->getProgramID());
		it.second->obj->draw();
	}
	return SUCCESS;
}


Node *SceneTree::getNode(std::string nodeName)
{
	return _nodes[nodeName];
}

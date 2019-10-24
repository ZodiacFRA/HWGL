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


int SceneTree::insert(std::string parentName, std::string name,
			Obj *obj, Shader *shader)
{
	Node *parentNode;
	if (parentName == "")  // TERNAIRE
		parentNode = &_root;
	else
		parentNode = _nodes[parentName];
	// if (parentNode == _nodes.end())
	// 	return printError("Parent node not found!");
	Node *newNode = new Node;
	newNode->name = name;
	newNode->modelMatrix = glm::mat4(1.0);
	newNode->parent = parentNode;
	newNode->obj = obj;
	newNode->shader = shader;
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
		it.second->obj->draw();
	}
	return SUCCESS;
}


int SceneTree::translateNode(std::string nodeName, glm::vec3 translationMatrix)
{
	Node *node = _nodes[nodeName];
	// if (node == _nodes.end())
	// 	return printError("Node not found!");
	node->modelMatrix = glm::translate(node->modelMatrix, translationMatrix);
	return SUCCESS;
}

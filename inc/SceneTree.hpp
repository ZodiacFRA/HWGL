#ifndef SCENE_TREE_HPP
#define SCENE_TREE_HPP

#include "commonHWGL.hpp"
#include "Obj.hpp"
#include "Shader.hpp"

struct Node;
struct Node {
	std::string name;
	glm::mat4 modelMatrix;

	Node *parent;
	std::vector<Node *> childs;

	Obj *obj;
	Shader *shader;
};


class SceneTree {
// Not implementing a real tree algorithm for now.
// I'll traverse the graph only to get all parents transformation
// matrices before drawing an object.
// If later a lot of depth is used I'll implement a proper
// graph traversal algorithm.
public:
	SceneTree();
	virtual ~SceneTree();
	int draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);
	int insert(std::string parentName, std::string name,
			Obj *obj, Shader *shader);
	int translateNode(std::string nodeName, glm::vec3 translationMatrix);

private:
	Node _root;

	std::map<std::string, Node *> _nodes;
};

#endif

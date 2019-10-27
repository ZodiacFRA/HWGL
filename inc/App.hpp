#ifndef APP_HPP
#define APP_HPP

#include "commonHWGL.hpp"
#include "Obj.hpp"
#include "Shader.hpp"
#include "SceneTree.hpp"
#include "Texture.hpp"


class App {
public:
	App();
	~App();

	int init();
	int run();

private:
	int initGLFW();
	int initGLEW();
	int initVertexArray();

	int initShaders();
	int loadObjsLibrary();
	int loadTextureLibrary();

	int setupScene();
	Node *createNode(std::string parentNodeName, std::string nodeName,
			std::string objName, std::string shaderName,
			std::string textureName, glm::vec3 position);

	int computeMatricesFromInputs(bool perspective_cam, float fov,
					bool controlled);

	void handleTime();
	int handleAspectRatio();

	// Game
	int moveFloor();


	// Utils
	int _winWidth;
	int _winHeight;
	double _lastTime;
	double _currentTime;
	float _deltaTime;
	int _nbFrames;
	float _worldSpeed;
	float _distMoved;  // Score?

	// GL
	GLFWwindow *_win;
	GLuint _vertexArrayID;

	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;

	// Camera
	glm::vec3 _camPos;
	float _hAngle;
	float _vAngle;
	double _xMouse;
	double _yMouse;

 	// TODO rename to _shadersLibrary
	std::map<std::string, Shader *> _shaders;
	std::map<std::string, Obj *> _objsLibrary;
	std::map<std::string, Texture *> _textureLibrary;
	SceneTree _sceneTree;

	// Decor
	std::map<std::string, Node *> _sceneryNodes;
};

#endif //APP_HPP

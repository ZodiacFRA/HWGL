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
	int initTexture2D();

	int initShaders();
	int loadObjsLibrary();
	int loadTextureLibrary();

	int setupScene();
	Node *createNode(std::string parentNodeName, std::string nodeName,
			std::string objName, std::string shaderName,
			std::string textureName, glm::vec3 position, int randomID=-1);

	int computeMatricesFromInputs(bool perspective_cam, float fov,
					bool controlled);

	void handleTime();
	int handleAspectRatio();

	// Game
	int moveScenery();
	int addBorders();
	int addProps();
	int moveFloor(glm::vec3 worldM);
	int moveObjects(glm::vec3 worldM);
	int handleSingleObjMovement(std::pair<std::string, Node*> it,
			glm::vec3 worldM, std::vector<std::string> &toDelete);
	int createRandomProp(std::string name, int x);
	int handleCollision(Node *Node);

	// Player
	int handlePlayerMovement();
	int handleJump();
	int handleMove();

	// Fonts
	void printText2D(const char * text, int x, int y, int size);
	void cleanupText2D();

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
	std::map<std::string, Shader *> _shadersLibrary;
	std::map<std::string, Obj *> _objsLibrary;
	std::map<std::string, Texture *> _textureLibrary;
	SceneTree _sceneTree;

	// Decor
	std::map<std::string, Node *> _sceneryNodes;

	// Player
	Node *_playerNode;
	float _jumpStart;
	int _lives;
	int _score;

	// Fonts
	unsigned int _text2DTextureID;
	unsigned int _text2DVertexBufferID;
	unsigned int _text2DUVBufferID;
	unsigned int _text2DShaderID;
	unsigned int _text2DUniformID;
	Texture _fontTexture;
	Shader _fontShader;
	float _fps;

	// ShakeScreen
	bool _shake;
	double _shakeStartTime;
};

#endif //APP_HPP

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
	int createNode(std::string parentNodeName, std::string nodeName,
			std::string objName, std::string shaderName,
			std::string textureName, glm::vec3 position);

	int computeMatricesFromInputs();

	void handleTime();
	int handleAspectRatio();

	// Utils
	int _winWidth;
	int _winHeight;
	double _lastTime;
	int _nbFrames;
	double _currentTime;

	GLFWwindow *_win;
	GLuint _vertexArrayID;

	// May move to each shader
	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;

	// Camera
	glm::vec3 _camPos;
	float _hAngle;
	float _vAngle;
	double _xMouse;
	double _yMouse;

	std::map<std::string, Shader *> _shaders; // TODO rename to _shadersLibrary
	std::map<std::string, Obj *> _objsLibrary;
	std::map<std::string, Texture *> _textureLibrary;
	SceneTree _sceneTree;
};

#endif //APP_HPP

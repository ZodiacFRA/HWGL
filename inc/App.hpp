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
	int initShaders();
	int loadObjsLibrary();
	int loadTextureLibrary();
	int initVertexArray();
	int setupScene();

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

	GLuint _lightID;
	glm::vec3 _lightPos;
	int initLights();
	int drawLights();
};

#endif //APP_HPP

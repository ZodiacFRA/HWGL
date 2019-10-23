#ifndef APP_HPP
#define APP_HPP

#include "commonHWGL.hpp"
#include "Obj.hpp"
#include "Shader.hpp"


class App {
public:
	App();
	~App();
	static App &get();  // Singleton

	int init();
	int run();

private:
	int initGLFW();
	int initGLEW();
	int initShaders();
	int initVertexArray();

	int computeMatricesFromInputs();
	int handleAspectRatio();

	// TODO move to scene tree
	int initLights();
	int drawLights();

	int _winWidth;
	int _winHeight;

	GLFWwindow *_win;
	GLuint _vertexArrayID;

	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;

	std::map<std::string, Shader *> _shaders;

	// Camera
	glm::vec3 _camPos;  // Initial position : on +Z
	float _hAngle;	// Initial horizontal angle : toward -Z
	float _vAngle; 	// Initial vertical angle : none
	double _xMouse;
	double _yMouse;

	GLuint _lightID;
	glm::vec3 _lightPos;

	// TODO move to scene tree
	Obj _tmpObj;
};

#endif //APP_HPP

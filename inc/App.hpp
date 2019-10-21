#ifndef APP_HPP
#define APP_HPP

#include "commonHWGL.hpp"
#include "shader.hpp"
#include "Obj.hpp"


class App {
public:
	App();
	~App();
	static App &get();  // Singleton

	// Inits
	int init();
	int initGLFW();
	int initGLEW();
	int initShaders();
	int initVertexArray();
	int initMatricesIDs();
	int initLights();

	int run();
	int drawObjects();
	int computeMatricesFromInputs();

	// TODO move to scene tree
	int drawLights();

private:
	GLFWwindow *_win;
	GLuint _programID;
	GLuint _matrixID;
	GLuint _viewMatrixID;
	GLuint _modelMatrixID;
	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;
	GLuint _vertexArrayID;

	// Initial position : on +Z
	glm::vec3 _camPos;
	// Initial horizontal angle : toward -Z
	float _hAngle;
	// Initial vertical angle : none
	float _vAngle;

	// TODO move to scene tree
	GLuint _lightID;
	glm::vec3 _lightPos;
	Obj _tmpObj;
};

#endif //APP_HPP

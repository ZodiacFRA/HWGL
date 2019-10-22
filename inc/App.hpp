#ifndef APP_HPP
#define APP_HPP

#include "shader.hpp"
#include "texture.hpp"

#include "commonHWGL.hpp"
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

	int run();
	int drawObjects();
	int computeMatricesFromInputs();

	// TODO move to scene tree
	int initLights();
	int drawLights();
	int handleTexture();
	int initTexture();

private:
	GLFWwindow *_win;
	GLuint _programID;
	GLuint _matrixID;
	GLuint _viewMatrixID;
	GLuint _modelMatrixID;
	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;
	GLuint _vertexArrayID;

	// Camera
	glm::vec3 _camPos;  // Initial position : on +Z
	float _hAngle;	// Initial horizontal angle : toward -Z
	float _vAngle; 	// Initial vertical angle : none
	double _xMouse;
	double _yMouse;

	// TODO move to scene tree
	GLuint _lightID;
	glm::vec3 _lightPos;
	Obj _tmpObj;
	GLuint _texture;
	GLuint _textureID;
};

#endif //APP_HPP

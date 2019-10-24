#ifndef SHADER_HPP
#define SHADER_HPP

#include "commonHWGL.hpp"

class Shader {
public:
	int loadShaders(const char *v_path, const char *f_path);
	virtual ~Shader();

	int setupDraw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix,
			glm::mat4 modelMatrix);

	// GETTERS
	GLuint getProgramID() { return _programID; }

private:
	GLuint _programID;

	GLuint _matrixID;
	GLuint _modelMatrixID;
	GLuint _viewMatrixID;

	int loadShader(GLuint shaderID, const char *path);
	int initMatricesIDs();
};

#endif

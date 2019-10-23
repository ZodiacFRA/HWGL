#ifndef SHADER_HPP
#define SHADER_HPP

#include "texture.hpp"
#include "commonHWGL.hpp"

class Shader {
public:
	int loadShaders(const char *v_path, const char *f_path);
	int loadTexture(const char *t_path);
	virtual ~Shader ();

	int setupDraw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix,
			glm::mat4 modelMatrix);

private:
	GLuint _programID;

	GLuint _matrixID;
	GLuint _modelMatrixID;
	GLuint _viewMatrixID;

	GLuint _texture;
	GLuint _textureID;

	int loadShader(GLuint shaderID, const char *path);
	int initMatricesIDs();

};

#endif

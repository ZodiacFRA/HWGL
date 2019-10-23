#include "Shader.hpp"

Shader::~Shader()
{
	glDeleteProgram(_programID);
}


int Shader::setupDraw(glm::mat4 projectionMatrix,
		glm::mat4 viewMatrix,
		glm::mat4 modelMatrix)
{
	glUseProgram(_programID);

	glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(_matrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(_modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(_viewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);

	// LIGHT ?

	// Texture handling
	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(_textureID, 0);

	return SUCCESS;
}


int Shader::initMatricesIDs()
{
	// Get a handle for our "MVP" uniform
	_matrixID = glGetUniformLocation(_programID, "MVP");
	_viewMatrixID = glGetUniformLocation(_programID, "V");
	_modelMatrixID = glGetUniformLocation(_programID, "M");
	return SUCCESS;
}

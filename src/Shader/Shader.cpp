#include "Shader.hpp"


Shader::~Shader()
{
	glDeleteProgram(_programID);
}


int Shader::setupDraw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix,
		glm::mat4 modelMatrix, glm::vec3 lightPos)
{
	glUseProgram(_programID);

	glUniform3f(_lightID, lightPos.x, lightPos.y, lightPos.z);

	glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(_matrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(_modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(_viewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);

	// LIGHT ?

	return SUCCESS;
}


int Shader::initMatricesIDs()
{
	// Get a handle for our "MVP" uniform
	_matrixID = glGetUniformLocation(_programID, "MVP");
	_viewMatrixID = glGetUniformLocation(_programID, "V");
	_modelMatrixID = glGetUniformLocation(_programID, "M");

	// Will be used only if shader does have a "LightPosition_worldspace"
	_lightID = glGetUniformLocation(_programID, "LightPosition_worldspace");

	return SUCCESS;
}

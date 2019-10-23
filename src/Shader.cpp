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


int Shader::loadTexture(const char *t_path)
{
	// If texture done with gimp:
	// export BMP as 24bits without colour space information
	_texture = loadBMP_custom(t_path);
	// _texture = loadDDS("./data/textures/uvmap.DDS");

	// Get a handle for our "myTextureSampler" uniform
	_textureID  = glGetUniformLocation(_programID, "myTextureSampler");
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


int Shader::loadShaders(const char *v_path, const char *f_path)
{
	GLint Result = GL_FALSE;
	int InfoLogLength;
	// Create the shaders
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	loadShader(vertexShaderID, v_path);
	loadShader(FragmentShaderID, f_path);

	printf("Linking shaders...\n");
	_programID = glCreateProgram();

	glAttachShader(_programID, vertexShaderID);
	glAttachShader(_programID, FragmentShaderID);

	glLinkProgram(_programID);

	// Check the program
	glGetProgramiv(_programID, GL_LINK_STATUS, &Result);
	glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(_programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
	// Clean
	glDetachShader(_programID, vertexShaderID);
	glDetachShader(_programID, FragmentShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(FragmentShaderID);

	initMatricesIDs();
	return SUCCESS;
}


int Shader::loadShader(GLuint shaderID, const char *path)
{
	GLint Result = GL_FALSE;
	int InfoLogLength;
	// Read the Shader code from file
	std::string shaderCode;
	std::ifstream shaderStream(path, std::ios::in);
	if (shaderStream.is_open()) {
		std::stringstream sstr;
		sstr << shaderStream.rdbuf();
		shaderCode = sstr.str();
		shaderStream.close();
	} else
		return printError("Impossible to open shader");

	// Compile Shader
	printf("Compiling shader : %s\n", path);
	char const * sourcePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &sourcePointer , NULL);
	glCompileShader(shaderID);

	// Check Shader
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> shaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(shaderID, InfoLogLength, NULL, &shaderErrorMessage[0]);
		printf("%s\n", &shaderErrorMessage[0]);
	}
	return SUCCESS;
}

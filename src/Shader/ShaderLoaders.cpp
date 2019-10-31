#include "Shader.hpp"


GLuint Shader::loadShaders(const char *v_path, const char *f_path)
{
	GLint Result = GL_FALSE;
	int InfoLogLength;
	// Create the shaders
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	loadShader(vertexShaderID, v_path);
	loadShader(FragmentShaderID, f_path);

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
	return _programID;
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
	printf("Compiling shader %s\n", path);
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

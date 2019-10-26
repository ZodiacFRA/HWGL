#include "App.hpp"


int App::init() {
	int flag = SUCCESS;
	flag &= initGLFW();
	flag &= initGLEW();
	flag &= initVertexArray();

	flag &= initShaders();
	flag &= loadObjsLibrary();
	flag &= loadTextureLibrary();

	flag &= setupScene();

	return flag;
}


int App::initGLFW()
{
	if (!glfwInit())
		return printError("Failed to initialize GLFW");

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	_win = glfwCreateWindow(_winWidth, _winHeight, WIN_NAME, NULL, NULL);
	if (_win == NULL)
		return printError("Failed to open GLFW window");
	glfwMakeContextCurrent(_win);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(_win, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(_win, _winWidth/2, _winHeight/2);

	// Set background color
	glClearColor(BG_COLOR);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
	return SUCCESS;
}


int App::initGLEW()
{
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK)
		return printError("Failed to initialize GLEW");
	return SUCCESS;
}


int App::initVertexArray()
{
	glGenVertexArrays(1, &_vertexArrayID);
	glBindVertexArray(_vertexArrayID);
	return SUCCESS;
}


int App::createNode(std::string parentNodeName, std::string nodeName,
		std::string objName, std::string shaderName,
		std::string textureName, glm::vec3 position)
{
	Obj *tmpObj = NULL;
	auto it = _objsLibrary.find(objName);
	if (it != _objsLibrary.end())
		tmpObj = it->second;
	else
		return printError("Can't create node (Obj does not exist)");

	Shader *tmpShader = NULL;
	auto it1 = _shaders.find(shaderName);
	if (it1 != _shaders.end())
		tmpShader = it1->second;
	else
		return printError("Can't create node (Shader does not exist)");

	Texture *tmpTexture = NULL;
	if (textureName != "") {
		auto it2 = _textureLibrary.find(textureName);
		if (it2 != _textureLibrary.end())
			tmpTexture = it2->second;
		else
			return printError("Can't create node (Texture does not exist)");
	}
	_sceneTree.insert(parentNodeName, nodeName, tmpObj, tmpShader,
				tmpTexture, position);
	return SUCCESS;
}

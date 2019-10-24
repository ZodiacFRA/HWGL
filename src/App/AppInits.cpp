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

	// flag &= initLights();  // TODO move to scene tree
	return flag;
}


int App::loadTextureLibrary()
{
	Texture *tmpTex = new Texture();
	tmpTex->loadTexture("./data/textures/suzUvPaint.bmp", false);
	_textureLibrary.emplace("suzUvPaint", tmpTex);
	return SUCCESS;
}


int App::loadObjsLibrary()
{
	Obj *tmpObj = new Obj("cubeUV"); // Name the mesh itself
	tmpObj->loadObj("./data/objs/cubeUV.obj");
	_objsLibrary.emplace("cubeUV", tmpObj);

	tmpObj = new Obj("suzanne");
	tmpObj->loadObj("./data/objs/suzanneMe.obj");
	_objsLibrary.emplace("suzanneMe", tmpObj);

	tmpObj = new Obj("terrain");
	tmpObj->loadObj("./data/objs/terrain.obj");
	_objsLibrary.emplace("terrain", tmpObj);
	return SUCCESS;
}


int App::initShaders()
{
	Shader *tmpShader = new Shader();
	tmpShader->loadShaders("./data/shaders/StandardShading/vs.glsl",
				"./data/shaders/StandardShading/fs.glsl"
	);
	_shaders.emplace("StandardShading", tmpShader);


	tmpShader = new Shader();
	tmpShader->loadShaders("./data/shaders/colored/vs.glsl",
				"./data/shaders/colored/fs.glsl"
	);
	_shaders.emplace("colored", tmpShader);

	return SUCCESS;
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


int App::initLights()
{
	// Get a handle for our "LightPosition" uniform
	// glUseProgram(_programID);
	// _lightID = glGetUniformLocation(_programID, "LightPosition_worldspace");
	return SUCCESS;
}


int App::createNode(std::string parentNodeName, std::string nodeName,
		std::string objName, std::string shaderName,
		std::string textureName, glm::vec3 position)
{
	Obj *tmpObj = _objsLibrary[objName];
	// CHECK IF OBJ EXISTS
	Shader *tmpShader = _shaders[shaderName];
	// CHECK IF SHADER EXISTS
	Texture *tmpTexture = _textureLibrary[textureName];
	// CHECK IF TEXTURE EXISTS
	_sceneTree.insert(parentNodeName, nodeName, tmpObj, tmpShader,
				tmpTexture, position);
	return SUCCESS;
}

#include "App.hpp"


int App::loadTextureLibrary()
{
	Texture *tmpTex = new Texture();
	tmpTex->loadTexture("./data/textures/Player.bmp", false);
	_textureLibrary.emplace("Player", tmpTex);

	tmpTex = new Texture();
	tmpTex->loadTexture("./data/textures/final_floortexture.bmp", false);
	_textureLibrary.emplace("floortexture", tmpTex);

	tmpTex = new Texture();
	tmpTex->loadTexture("./data/textures/cube.bmp", false);
	_textureLibrary.emplace("cube", tmpTex);
	return SUCCESS;
}


int App::loadObjsLibrary()
{
	Obj *tmpObj = new Obj("axis"); // Name of the mesh itself
	tmpObj->loadObj("./data/objs/axis.obj");
	_objsLibrary.emplace("axis", tmpObj);

	tmpObj = new Obj("cube");
	tmpObj->loadObj("./data/objs/cube.obj");
	_objsLibrary.emplace("cube", tmpObj);

	tmpObj = new Obj("rect");
	tmpObj->loadObj("./data/objs/rect.obj");
	_objsLibrary.emplace("rectFloor", tmpObj);

	tmpObj = new Obj("Player");
	tmpObj->loadObj("./data/objs/Player.obj");
	_objsLibrary.emplace("Player", tmpObj);
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

	tmpShader = new Shader();
	tmpShader->loadShaders("./data/shaders/StandardShadingNoSpec/vs.glsl",
				"./data/shaders/StandardShadingNoSpec/fs.glsl"
	);
	_shaders.emplace("StandardShadingNoSpec", tmpShader);

	return SUCCESS;
}

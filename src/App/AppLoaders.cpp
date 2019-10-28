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

	tmpObj = new Obj("obs0");
	tmpObj->loadObj("./data/objs/obs0.obj");
	_objsLibrary.emplace("obs0", tmpObj);

	tmpObj = new Obj("obs1");
	tmpObj->loadObj("./data/objs/obs1.obj");
	_objsLibrary.emplace("obs1", tmpObj);

	tmpObj = new Obj("obs2");
	tmpObj->loadObj("./data/objs/obs2.obj");
	_objsLibrary.emplace("obs2", tmpObj);

	tmpObj = new Obj("obs3");
	tmpObj->loadObj("./data/objs/obs3.obj");
	_objsLibrary.emplace("obs3", tmpObj);

	tmpObj = new Obj("obs4");
	tmpObj->loadObj("./data/objs/obs4.obj");
	_objsLibrary.emplace("obs4", tmpObj);
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

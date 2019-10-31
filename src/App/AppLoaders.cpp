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

	tmpTex = new Texture();
	tmpTex->loadTexture("./data/textures/dev.bmp", false);
	_textureLibrary.emplace("dev", tmpTex);

	tmpTex = new Texture();
	tmpTex->loadTexture("./data/textures/point.bmp", false);
	_textureLibrary.emplace("point", tmpTex);

	tmpTex = new Texture();
	tmpTex->loadTexture("./data/textures/bonus.bmp", false);
	_textureLibrary.emplace("bonus", tmpTex);

	tmpTex = new Texture();
	tmpTex->loadTexture("./data/textures/red.bmp", false);
	_textureLibrary.emplace("malus", tmpTex);
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

	tmpObj = new Obj("point");
	tmpObj->loadObj("./data/objs/point.obj");
	_objsLibrary.emplace("point", tmpObj);

	tmpObj = new Obj("bonus");
	tmpObj->loadObj("./data/objs/bonus.obj");
	_objsLibrary.emplace("bonus", tmpObj);

	tmpObj = new Obj("malus");
	tmpObj->loadObj("./data/objs/malus.obj");
	_objsLibrary.emplace("malus", tmpObj);
	return SUCCESS;
}


int App::initShaders()
{
	Shader *tmpShader = new Shader();
	tmpShader->loadShaders("./data/shaders/StandardShading/vs.glsl",
				"./data/shaders/StandardShading/fs.glsl"
	);
	_shadersLibrary.emplace("StandardShading", tmpShader);


	tmpShader = new Shader();
	tmpShader->loadShaders("./data/shaders/colored/vs.glsl",
				"./data/shaders/colored/fs.glsl"
	);
	_shadersLibrary.emplace("colored", tmpShader);

	tmpShader = new Shader();
	tmpShader->loadShaders("./data/shaders/StandardShadingNoSpec/vs.glsl",
				"./data/shaders/StandardShadingNoSpec/fs.glsl"
	);
	_shadersLibrary.emplace("StandardShadingNoSpec", tmpShader);

	return SUCCESS;
}

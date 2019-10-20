#include "App.hpp"


App::App()
	// : _winName(WIN_NAME), _winWidth(WIN_WIDTH), _winHeight(WIN_HEIGHT),
	// _yFov(45.0f), _running(true), _deltaTime(0.0f), _lastTime(0.0f)
{}

App::~App()
{
	// glfwTerminate();  // Destroy all windows and release resources
}

App &App::get()
{
	static App app;
	return app;
}

int App::run()
{
	return SUCCESS;
}

int App::init() {
	return SUCCESS;
}

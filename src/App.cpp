#include "App.hpp"


App::App()
{}

App::~App()
{
	glDeleteProgram(_programID);
	glfwTerminate();
}

App &App::get()
{
	static App app;
	return app;
}

int App::run()
{
	do {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Use our shader
		glUseProgram(_programID);



		// Swap buffers
		glfwSwapBuffers(_win);
		glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(_win, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(_win) == 0 );
	return SUCCESS;
}

int App::init() {
	int flag = SUCCESS;
	flag &= initGLFW();
	flag &= initGLEW();
	flag &= initShaders();
	return flag;
}

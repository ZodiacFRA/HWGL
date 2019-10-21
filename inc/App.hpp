#ifndef APP_HPP
#define APP_HPP

#include "commonHWGL.hpp"
#include "shader.hpp"

class App {
public:
	App();
	~App();
	static App &get();  // Singleton

	// Inits
	int init();
	int initGLFW();
	int initGLEW();
	int initShaders();

	int run();

private:
	GLFWwindow *_win;
	GLuint _programID;
};

#endif //APP_HPP

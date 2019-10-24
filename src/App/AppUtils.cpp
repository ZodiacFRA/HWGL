#include "App.hpp"


int App::handleAspectRatio()
{
	// Handles window resize, I successfully change the aspectRatio
	// but not the window limits, even when calling glfwSetWindowSizeLimits
	static int oldWinWidth = _winWidth;
	static int oldWinHeight = _winHeight;
	// Check if window as been resized
	glfwGetWindowSize(_win, &_winWidth, &_winHeight);
	if (_winWidth != oldWinWidth || _winHeight != oldWinHeight) {
		glfwSetWindowSizeLimits(_win, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE);
		glfwSetWindowAspectRatio(_win, GLFW_DONT_CARE, GLFW_DONT_CARE);
		oldWinWidth = _winWidth;
	}
	return SUCCESS;
}


void App::handleTime()
{
	_currentTime = glfwGetTime();
	_nbFrames++;
	double deltaTime = _currentTime - _lastTime;
	if (deltaTime >= FPS_PRINT_INTERVAL) {
		printf("%f fps\n", double(_nbFrames) / deltaTime);
		_nbFrames = 0;
		_lastTime += deltaTime;
	}
}

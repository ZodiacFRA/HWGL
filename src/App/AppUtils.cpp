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
	_deltaTime = _currentTime - _lastTime;
	_lastTime = _currentTime;

	// FPS counter
	_nbFrames++;
	static float lastFrameTime = glfwGetTime();
	if (_currentTime - lastFrameTime >= FPS_PRINT_INTERVAL) {
		printf("%f fps\n", float(_nbFrames) / (_currentTime - lastFrameTime));
		_nbFrames = 0;
		lastFrameTime = _currentTime;
	}
}

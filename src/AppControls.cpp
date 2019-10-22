#include "App.hpp"


int App::computeMatricesFromInputs()
{
	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// FOR DEBUG, inputs works fine
	// static double oldXMouse = _xMouse;
	// static double oldYMouse = _yMouse;

	// Get mouse position
	glfwGetCursorPos(_win, &_xMouse, &_yMouse);

	// FOR DEBUG, inputs works fine
	// if (_xMouse != oldXMouse || _yMouse != oldYMouse)
	// 	printf("oldXMouse = %f, newXMouse = %f\noldYMouse = %f, newYMouse = %f\n", oldXMouse, _xMouse, oldYMouse, _yMouse);
	// oldXMouse = _xMouse;
	// oldYMouse = _yMouse;

	// Reset mouse position for next frame
	glfwSetCursorPos(_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);

	// Compute new orientation
	_hAngle += MOUSE_MOV_SPEED * float(WIN_WIDTH / 2 - _xMouse);
	_vAngle += MOUSE_MOV_SPEED * float(WIN_HEIGHT / 2 - _yMouse);

	// FOR DEBUG, inputs works fine
	// printf("hAngle = %f, vAngle = %f\n", _hAngle, _vAngle);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(_vAngle) * sin(_hAngle),
		sin(_vAngle),
		cos(_vAngle) * cos(_hAngle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(_hAngle - 3.14f / 2.0f),
		0,
		cos(_hAngle - 3.14f / 2.0f)
	);
	// Up vector
	glm::vec3 up = glm::cross(right, direction);

	// Handle key inputs for cam movement
	if (glfwGetKey(_win, GLFW_KEY_UP) == GLFW_PRESS)
		_camPos += direction * deltaTime * CAM_MOV_SPEED;
	if (glfwGetKey(_win, GLFW_KEY_DOWN) == GLFW_PRESS)
		_camPos -= direction * deltaTime * CAM_MOV_SPEED;
	if (glfwGetKey(_win, GLFW_KEY_RIGHT) == GLFW_PRESS)
		_camPos += right * deltaTime * CAM_MOV_SPEED;
	if (glfwGetKey(_win, GLFW_KEY_LEFT) == GLFW_PRESS)
		_camPos -= right * deltaTime * CAM_MOV_SPEED;

	// FOR DEBUG, inputs works fine
	// std::cout << _camPos[0]  << " - " << _camPos[1] << " - " << _camPos[2] << '\n';

	// Projection matrix : 4:3 ratio, display range : 0.1 unit <-> 100 units
	_projectionMatrix = glm::perspective(glm::radians(FOV), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	_viewMatrix = glm::lookAt(
			_camPos,             // Camera is here
			_camPos + direction, // and looks here : at the same position, plus "direction"
			up                    // Head is up (set to 0,-1,0 to look upside-down)
	);
	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
	return SUCCESS;
}

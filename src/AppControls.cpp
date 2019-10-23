#include "App.hpp"


int App::computeMatricesFromInputs()
{
	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	glfwGetCursorPos(_win, &_xMouse, &_yMouse);

	// Reset mouse position for next frame
	glfwSetCursorPos(_win, _winWidth / 2, _winHeight / 2);

	// Compute new orientation
	_hAngle += MOUSE_MOV_SPEED * float(_winWidth / 2 - _xMouse);
	_vAngle += MOUSE_MOV_SPEED * float(_winHeight / 2 - _yMouse);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(_vAngle) * sin(_hAngle),
		sin(_vAngle),
		cos(_vAngle) * cos(_hAngle)
	);
	// printVec3(direction);
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(_hAngle - 3.14f / 2.0f),
		0,
		cos(_hAngle - 3.14f / 2.0f)
	);
	// Up vector
	glm::vec3 up = glm::cross(right, direction);

	// Handle key inputs for cam movement
	if (glfwGetKey(_win, GLFW_KEY_W) == GLFW_PRESS)
		_camPos += direction * deltaTime * CAM_MOV_SPEED;
	if (glfwGetKey(_win, GLFW_KEY_S) == GLFW_PRESS)
		_camPos -= direction * deltaTime * CAM_MOV_SPEED;
	if (glfwGetKey(_win, GLFW_KEY_D) == GLFW_PRESS)
		_camPos += right * deltaTime * CAM_MOV_SPEED;
	if (glfwGetKey(_win, GLFW_KEY_A) == GLFW_PRESS)
		_camPos -= right * deltaTime * CAM_MOV_SPEED;
	if (glfwGetKey(_win, GLFW_KEY_SPACE) == GLFW_PRESS)
		_camPos += up * deltaTime * CAM_MOV_SPEED;
	if (glfwGetKey(_win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		_camPos -= up * deltaTime * CAM_MOV_SPEED;

	// Projection matrix : fov, ratio, display range : 0.1 unit <-> 100 units
	_projectionMatrix = glm::perspective(
				glm::radians(FOV),
				float(_winWidth) / float(_winHeight),
				0.01f, 1000.0f);

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

#include "App.hpp"


int App::computeMatricesFromInputs(bool perspective_cam, float fov,
					bool controlled)
{
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
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(_hAngle - 3.14f / 2.0f),
		0,
		cos(_hAngle - 3.14f / 2.0f)
	);
	// Up vector
	glm::vec3 up = glm::cross(right, direction);

	// Handle key inputs for cam movement
	if (controlled) {
		if (glfwGetKey(_win, GLFW_KEY_W) == GLFW_PRESS)
			_camPos += direction * _deltaTime * CAM_MOV_SPEED;
		if (glfwGetKey(_win, GLFW_KEY_S) == GLFW_PRESS)
			_camPos -= direction * _deltaTime * CAM_MOV_SPEED;
		if (glfwGetKey(_win, GLFW_KEY_D) == GLFW_PRESS)
			_camPos += right * _deltaTime * CAM_MOV_SPEED;
		if (glfwGetKey(_win, GLFW_KEY_A) == GLFW_PRESS)
			_camPos -= right * _deltaTime * CAM_MOV_SPEED;
		if (glfwGetKey(_win, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
			_camPos -= up * _deltaTime * CAM_MOV_SPEED;
		if (glfwGetKey(_win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			_camPos += up * _deltaTime * CAM_MOV_SPEED;
	}

	if (perspective_cam) {  // Projection matrix
		// fov, ratio, display range
		_projectionMatrix = glm::perspective(
					glm::radians(fov),
					float(_winWidth) / float(_winHeight),
					0.01f, 5000.0f);
	} else {
		// limits left, right, bottom, top, display range
		_projectionMatrix = glm::ortho(0, 400, 0, 400, -1, 1);
	}
	if (controlled) {  // Camera matrix
		_viewMatrix = glm::lookAt(
				_camPos,             // Camera is here
				_camPos + direction, // and looks here : at the same position, plus "direction"
				up);                 // Head is up (set to 0,-1,0 to look upside-down)
	} else if (_shake) {  // screen shake effect
		int tmpRand = rand() % 10 - 5;
		float final = float(tmpRand) / 10;
		if (_currentTime - _shakeStartTime > 0.1)
			_shake = false;
		_viewMatrix = glm::lookAt(
				_camPos,
				glm::vec3(final, final, -6),
				glm::vec3(0, 1, 0));
	} else {
		_viewMatrix = glm::lookAt(
				_camPos,
				glm::vec3(0, 0, -6),
				glm::vec3(0, 1, 0));
	}
	return SUCCESS;
}

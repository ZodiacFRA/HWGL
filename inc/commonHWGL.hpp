#ifndef GLSCENE_COMMON
#define GLSCENE_COMMON

#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <string.h> // for memcmp
#include <cstring>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include <GL/glew.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/euler_angles.hpp>
#include <gtx/quaternion.hpp>
#include <gtx/norm.hpp>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#define FAILURE 0
#define SUCCESS 1

#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define WIN_NAME "HWGL"

#define BG_COLOR 0.27f, 0.28f, 0.34f, 0.0f

#define FOV 45.0f
#define CAM_MOV_SPEED 3.0f
#define MOUSE_MOV_SPEED 0.005f
#define H_ANGLE 3.14f
#define V_ANGLE 0.0f

#define VERTEX_SHADER "./data/shaders/StandardShading.vertexshader"
#define FRAGMENT_SHADER "./data/shaders/StandardShading.fragmentshader"

#define C_RED "\x1b[31m"
#define C_GREEN "\x1b[32m"
#define C_BOLD_GREEN "\x1b[1;32m"
#define C_GREEN "\x1b[32m"
#define C_YELLOW "\x1b[33m"
#define C_BLUE "\x1b[36m"
#define C_RESET "\x1b[0m"

int printError(std::string msg);

#endif //GLSCENE_COMMON

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
#include <random>
#include <vector>
#include <cmath>
#include <map>

#include <GL/glew.h>
#include <gtc/matrix_transform.hpp>
#include <gtx/euler_angles.hpp>
#include <gtx/string_cast.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>
#include <gtx/norm.hpp>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#define FAILURE 0
#define SUCCESS 1

#define WIN_WIDTH 1920/2
#define WIN_HEIGHT 1050
#define WIN_NAME "HWGL"

#define BG_COLOR 0, 0, 0, 0
#define FPS_PRINT_INTERVAL 4.0

#define CAM_MOV_SPEED 60.0f
#define MOUSE_MOV_SPEED 0.0001f

#define C_RED "\x1b[31m"
#define C_GREEN "\x1b[32m"
#define C_BOLD_GREEN "\x1b[1;32m"
#define C_GREEN "\x1b[32m"
#define C_YELLOW "\x1b[33m"
#define C_BLUE "\x1b[36m"
#define C_RESET "\x1b[0m"

int printError(std::string msg);
float getRandomFloat(float min, float max);

#endif //GLSCENE_COMMON

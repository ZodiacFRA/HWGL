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

#define C_RED "\x1b[31m"
#define C_GREEN "\x1b[32m"
#define C_BOLD_GREEN "\x1b[1;32m"
#define C_GREEN "\x1b[32m"
#define C_YELLOW "\x1b[33m"
#define C_BLUE "\x1b[36m"
#define C_RESET "\x1b[0m"

#endif //GLSCENE_COMMON

#include "commonHWGL.hpp"


int printError(std::string msg)
{
	std::cout << C_RED << msg << C_RESET << std::endl;
	return FAILURE;
}

int printVec3(glm::vec3 vec)
{
	std::cout << vec[0]  << " - " << vec[1] << " - " << vec[2] << std::endl;
	return FAILURE;
}

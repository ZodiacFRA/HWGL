#include "commonHWGL.hpp"


int printError(std::string msg)
{
	std::cout << C_RED << msg << C_RESET << std::endl;
	return FAILURE;
}


auto &getGen()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	return gen;
}


float getRandomFloat(float min, float max)
{
	std::uniform_real_distribution<float> randFloat(min, max);
        return randFloat(getGen());
}

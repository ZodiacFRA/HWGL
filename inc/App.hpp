#ifndef APP_HPP
#define APP_HPP

#include "commonHWGL.hpp"


class App {
public:
	App();
	~App();
	static App &get();

	// Inits
	int init();
	int run();
};

#endif //APP_HPP

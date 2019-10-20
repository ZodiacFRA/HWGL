#include "App.hpp"


GLFWwindow* window;


int main(int ac, char **av)
{
	App app = App::get();  // Set Width and Height to 0 for fullscreen
	if (app.init() == FAILURE) {
		printf("%sApp init failed!%s\n", C_RED, C_RESET);
		return FAILURE;
	}
	printf("%sApp init OK%s\n", C_BOLD_GREEN, C_RESET);
	return app.run();
}

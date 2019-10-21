#include "App.hpp"


GLFWwindow* window;


int main(int ac, char **av)
{
	App app = App::get();
	if (app.init() == FAILURE)
		return printError("App init failed!");
	printf("%sApp init OK%s\n", C_BOLD_GREEN, C_RESET);
	return app.run();
}

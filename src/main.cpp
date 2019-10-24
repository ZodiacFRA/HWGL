#include "App.hpp"


int main()
{
	App app = App();
	if (app.init() == FAILURE)
		return printError("App init failed!");
	printf("%sInitialization done, launching%s\n", C_BOLD_GREEN, C_RESET);
	return app.run();
}

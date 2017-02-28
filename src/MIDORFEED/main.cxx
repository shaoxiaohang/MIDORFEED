#include<MIDORFEED/Application.h>

int main(int argc, char** argv)
{
	vrv::Application* app = new vrv::Application();
	app->initialize(800, 600, "main window");
	app->run();
	return 0;
}
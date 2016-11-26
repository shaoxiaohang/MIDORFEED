#include <MIDORFEED/Application.h>

using namespace vrv;

int main(int argc, char** argv)
{
	Application* application = new Application(1280, 960, "vrv");
	application->run();

	return 0;
}
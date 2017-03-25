#include<Render/MainWindow.h>
#include<Render/Context.h>
namespace vrv
{
	WindowConfiguration::WindowConfiguration(int _width, int _height, const std::string& _title)
		: width(_width)
		, height(_height)
		, title(_title)
		, depthBufferSize(32)
		, redBufferSize(8)
		, greenBufferSize(8)
		, blueBufferSize(8)
		, alphaBufferSize(8)
	{}

	MainWindow::MainWindow(Viewer* viewer, WindowConfiguration configuration)
		: myConfiguration(configuration)
		, myViewer(viewer)
	{}

}


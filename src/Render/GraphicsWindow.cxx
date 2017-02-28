#include<Render/GraphicsWindow.h>

namespace vrv
{
	WindowConfiguration::WindowConfiguration(int _width, int _height, const std::string& _title)
		: width(_width)
		, height(_height)
		, title(_title)
	{}

	GraphicsWindow::GraphicsWindow(WindowConfiguration configuration)
		: myConfiguration(configuration)
		, myContext(0)
	{}
}


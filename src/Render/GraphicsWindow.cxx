#include<Render/GraphicsWindow.h>
#include<Render/Context.h>
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

	Context* GraphicsWindow::context()
	{
		return myContext;
	}

	void GraphicsWindow::createContext()
	{
		myContext = new Context();
	}
}


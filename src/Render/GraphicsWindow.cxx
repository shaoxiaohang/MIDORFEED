#include<Render/GraphicsWindow.h>

namespace vrv
{
	GraphicsWindow::GraphicsWindow(int width, int height, const std::string& title, WINDOWFLAG flag)
		: myWidth(width)
		, myHeight(height)
		, myTitle(title)
		, myFlag(flag)
	{
		//left empty
	}

	GraphicsWindow::~GraphicsWindow()
	{
		//left empty
	}
}
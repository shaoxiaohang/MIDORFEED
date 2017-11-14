#pragma once

#include <string>

namespace vrv
{
	class Context;
	class Viewer;

	struct WindowConfiguration
	{
		WindowConfiguration(int width, int height, const std::string& title);

		int width;
		int height;
		std::string title;

		int depthBufferSize;
		int stentilBufferSize;
		int redBufferSize;
		int greenBufferSize;
		int blueBufferSize;
		int alphaBufferSize;
	};

	class MainWindow
	{
	public:

		int width();
		int height();

	protected:

		MainWindow(WindowConfiguration configuration);
		virtual void initialize() = 0;
	protected:
		
		WindowConfiguration myConfiguration;

	};
}
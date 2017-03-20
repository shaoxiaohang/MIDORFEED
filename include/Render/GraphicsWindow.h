#pragma once

#include <string>

namespace vrv
{
	class Context;

	struct WindowConfiguration
	{
		WindowConfiguration(int width, int height, const std::string& title);

		int width;
		int height;
		std::string title;
	};

	class GraphicsWindow
	{
	public:

		virtual void show() = 0;
		virtual bool shouldClose() = 0;
		virtual void swapBuffer() = 0;
		virtual void makeContexCurrent() = 0;
		virtual void pullEvents() = 0;
		virtual Context* context();
		virtual void createContext();

	protected:

		GraphicsWindow(WindowConfiguration configuration);
		virtual bool initialize() = 0;

	protected:
		
		WindowConfiguration myConfiguration;
		Context* myContext;

	};
}
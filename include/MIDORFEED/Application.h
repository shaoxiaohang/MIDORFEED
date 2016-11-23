#pragma once

#include<string>

namespace vrv
{
	class GraphicsWindow;

	class Application
	{
	public:

		Application(int width, int height, const std::string& title);

		void run();

	protected:

		GraphicsWindow* myWindow;
	};
}
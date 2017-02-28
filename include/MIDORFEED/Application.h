#pragma once
#include<string>
namespace vrv
{
	class Device;
	class GraphicsWindow;

	class Application
	{
	public:
		Application();

		virtual void run();

		virtual void initialize(int width, int height, const std::string& title);

	protected:
		Device* myDevice;
		GraphicsWindow* myMainWindow;
	};
}
#pragma once
#include<string>

namespace vrv
{
	class GraphicsWindow
	{
	public:
		enum WINDOWFLAG
		{
			WINDOWED,
			FULLSCREEN
		};

		GraphicsWindow(int width, int height, const std::string& title, WINDOWFLAG flag = WINDOWED);

		virtual ~GraphicsWindow();

		virtual void initialize() = 0;

		virtual bool isClosed() = 0;

		virtual void pollEvents() = 0;

		virtual void swapBuffers() = 0;

	protected:

		int myWidth;
		int myHeight;
		std::string myTitle;
		WINDOWFLAG myFlag;
	};
}
#pragma once

#include<Render/GraphicsWindow.h>

struct GLFWwindow;

namespace vrv
{
	class GLFWGraphicsWindow : public GraphicsWindow
	{
	public:

		GLFWGraphicsWindow(int width, int height, const std::string& title, 
							GraphicsWindow::WINDOWFLAG flag);

		virtual ~GLFWGraphicsWindow();

		virtual void initialize();

		virtual bool isClosed();

		virtual void pollEvents();

		virtual void swapBuffers();

	protected:
		GLFWwindow* myGLFWWindow;
	};
}
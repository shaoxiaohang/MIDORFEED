#pragma once

#include<Render/GraphicsWindow.h>

struct GLFWwindow;

namespace vrv
{
	class Context;
	class GLFWGraphicsWindow : public GraphicsWindow
	{
		friend class GLEWDevice;
	public:

		virtual void show();
		virtual bool shouldClose();
		virtual void swapBuffer();
		virtual void makeContexCurrent();
		virtual void pullEvents();

	protected:

		GLFWGraphicsWindow(WindowConfiguration config);
		~GLFWGraphicsWindow();

		virtual bool initialize();

	protected:
		Context* myContext;
		GLFWwindow* myGLFWwindow;
	};
}
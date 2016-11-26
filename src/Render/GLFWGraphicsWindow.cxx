#include <Render/GLFWGraphicsWindow.h>
#include <GLFW/glfw3.h>

namespace vrv
{

	GLFWGraphicsWindow::GLFWGraphicsWindow(int width, int height, const std::string& title,
		GraphicsWindow::WINDOWFLAG flag)
		:GraphicsWindow(width, height, title, flag)
	{
		//left empty
	}

	GLFWGraphicsWindow::~GLFWGraphicsWindow()
	{
		glfwTerminate();
	}

	void GLFWGraphicsWindow::initialize()
	{
		myGLFWWindow = glfwCreateWindow(myWidth, myHeight, myTitle.c_str(), 0, 0);
		glfwMakeContextCurrent(myGLFWWindow);
	}

	bool GLFWGraphicsWindow::isClosed()
	{
		if (glfwWindowShouldClose(myGLFWWindow) == 0)
		{
			return false;
		}
		return true;
	}

	void GLFWGraphicsWindow::pollEvents()
	{
		glfwPollEvents();
	}

	void GLFWGraphicsWindow::swapBuffers()
	{
		glfwSwapBuffers(myGLFWWindow);
	}

}
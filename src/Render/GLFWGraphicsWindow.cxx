#include <Render/GLFWGraphicsWindow.h>
#include <Render/Context.h>
#include <GLFW/glfw3.h>
namespace vrv
{
	GLFWGraphicsWindow::GLFWGraphicsWindow(WindowConfiguration config)
		: GraphicsWindow(config)
		, myGLFWwindow(0)
		, myContext(0)
	{
		//
	}

	GLFWGraphicsWindow::~GLFWGraphicsWindow()
	{
		if (myGLFWwindow)
		{
			myGLFWwindow = 0;
		}
	}

	void GLFWGraphicsWindow::show()
	{
		glfwShowWindow(myGLFWwindow);
	}


	bool GLFWGraphicsWindow::shouldClose()
	{
		int res = glfwWindowShouldClose(myGLFWwindow);
		return res != 0 ? true : false;
	}

	void GLFWGraphicsWindow::swapBuffer()
	{
		glfwSwapBuffers(myGLFWwindow);
	}

	void GLFWGraphicsWindow::makeContexCurrent()
	{
		glfwMakeContextCurrent(myGLFWwindow);
	}

	void GLFWGraphicsWindow::pullEvents()
	{
		glfwPollEvents();
	}

	bool GLFWGraphicsWindow::initialize()
	{
		myGLFWwindow = glfwCreateWindow(myConfiguration.width, myConfiguration.height, myConfiguration.title.c_str(), 0, 0);
		return myGLFWwindow ? true : false;
	}
}
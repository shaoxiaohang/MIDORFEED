#include <Render/GLEWDevice.h>
#include <Render/GLFWGraphicsWindow.h>
#define  GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>



namespace vrv
{
	GLEWDevice::GLEWDevice()
		:Device()
	{

	}

	void GLEWDevice::initialize()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		glewExperimental = GL_TRUE;
		glewInit();
	}

	GraphicsWindow* GLEWDevice::createWindow(int width, int height, const std::string& title,GraphicsWindow::WINDOWFLAG flag)
	{
		GLFWGraphicsWindow* window = 0;
		window = new GLFWGraphicsWindow(width, height, title, flag);
		window->initialize();
		return window;
	}

}
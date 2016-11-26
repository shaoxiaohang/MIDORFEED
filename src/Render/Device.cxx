#include <Render/Device.h>
#include <GL/glew.h>
#include <Render/GLFWGraphicsWindow.h>
namespace vrv
{
	Device*	Device::myInstance = 0;

	Device::Device()
	{
		myInstance = this;
	}

	Device* Device::instance()
	{
		return myInstance;
	}

}
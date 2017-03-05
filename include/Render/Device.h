#pragma once

#include <Render/GraphicsWindow.h>
#include <Core/UsefulMarco.h>
namespace vrv
{
	class ShaderProgram;
	class Device
	{
	public:
		virtual bool initialize() = 0;
		virtual GraphicsWindow* createGraphcisWindow(WindowConfiguration cofig) = 0;
		virtual ShaderProgram* createShaderProgram(const std::string& vertFile, const std::string& fragFile) = 0;

	protected:
		Device();

	private:
		DISALLOW_COPY_AND_ASSIGN(Device)
	};
}
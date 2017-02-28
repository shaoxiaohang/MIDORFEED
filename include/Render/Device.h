#pragma once

#include <Render/GraphicsWindow.h>
#include <Core/UsefulMarco.h>
namespace vrv
{
	class Device
	{
	public:
		virtual bool initialize() = 0;

		virtual GraphicsWindow* createGraphcisWindow(WindowConfiguration cofig) = 0;

	protected:
		Device();

	private:
		DISALLOW_COPY_AND_ASSIGN(Device)
	};
}
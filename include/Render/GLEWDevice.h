#pragma once

#include <Render/Device.h>

namespace vrv
{
	class GLEWDevice : public Device
	{
	public:
		GLEWDevice();

		virtual void initialize();

		virtual GraphicsWindow* createWindow(int width, int height, const std::string& title,
			GraphicsWindow::WINDOWFLAG = GraphicsWindow::WINDOWED);

		virtual VertexBuffer* createVertexBuffer(BufferUsage usage, int sizeInBytes);

		virtual IndexBuffer* createIndexBuffer(BufferUsage usage, int sizeInBytes);
	};
}
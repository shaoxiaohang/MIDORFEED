#pragma once

#include <string>
#include <Render/Buffer.h>
#include <Render/GraphicsWindow.h>

namespace vrv
{
	class GraphicsWindow;
	class IndexBuffer;
	class VertexBuffer;

	class Device
	{
	public:

		static Device* instance();

		virtual void initialize() = 0;

		virtual GraphicsWindow* createWindow(int width, int height, const std::string& title,
			GraphicsWindow::WINDOWFLAG = GraphicsWindow::WINDOWED) = 0;

		virtual IndexBuffer* createIndexBuffer(BufferUsage usage, int sizeInBytes) = 0;

		virtual VertexBuffer* createVertexBuffer(BufferUsage usage, int sizeInBytes) = 0;
		
	protected:

		Device();

		static Device* myInstance;

	};
}
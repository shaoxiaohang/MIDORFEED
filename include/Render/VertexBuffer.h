#pragma once

#include<Render/Buffer.h>
#include<Render/BufferObject.h>
namespace vrv
{
	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer(BufferUsage usage, int sizeInBytes);
	};
}
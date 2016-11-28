#pragma once

#include<Render/Buffer.h>
namespace vrv
{
	class IndexBuffer : public Buffer
	{
	public:
		IndexBuffer(BufferUsage usage, int sizeInBytes);
	};
}
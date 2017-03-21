#pragma once
#include <Render/BufferObject.h>
namespace vrv
{
	class IndexBufferObject : public BufferObject
	{
	public:
		IndexBufferObject(BufferUsage usage = BufferObject::STATIC_DRAW);
	};
}
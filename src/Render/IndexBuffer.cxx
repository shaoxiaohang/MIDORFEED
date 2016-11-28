#include <Render/IndexBuffer.h>

namespace vrv
{
	IndexBuffer::IndexBuffer(BufferUsage usage, int sizeInBytes)
		: Buffer(BufferTarget::ELEMENT_ARRAY_BUFFER, usage, sizeInBytes)
	{
		//empty
	}
}
#include<Render/VertexBuffer.h>
namespace vrv
{
	VertexBuffer::VertexBuffer(BufferUsage usage, int sizeInBytes)
		: Buffer(BufferTarget::ARRAY_BUFFER,usage,sizeInBytes)
	{
		//empty
	}
}
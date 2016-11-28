#include <Render/VertexBufferGL3X.h>
#include <Render/BufferObjectGL3X.h>
namespace vrv
{
	VertexBufferGL3X::VertexBufferGL3X(BufferUsage usage, int sizeInBytes)
		: VertexBuffer(usage,sizeInBytes)
	{
		myBufferObject = new BufferObjectGL3X(BufferTarget::ARRAY_BUFFER, usage, sizeInBytes);
	}

	void VertexBufferGL3X::copyFromSystemMemory(void* bufferSystemMemory, int sizeInBytes, int offsetInBytes)
	{
		myBufferObject->copyFromSystemMemory(bufferSystemMemory, sizeInBytes, offsetInBytes);
	}

	VertexBufferGL3X::~VertexBufferGL3X()
	{
		delete myBufferObject;
	}
}
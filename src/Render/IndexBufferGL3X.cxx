#include <Render/IndexBufferGL3X.h>
#include <Render/BufferObjectGL3X.h>
namespace vrv
{
	IndexBufferGL3X::IndexBufferGL3X(BufferUsage usage, int sizeInBytes)
		: IndexBuffer(usage, sizeInBytes)
	{
		myBufferObject = new BufferObjectGL3X(BufferTarget::ELEMENT_ARRAY_BUFFER, usage, sizeInBytes);
	}

	void IndexBufferGL3X::copyFromSystemMemory(void* bufferSystemMemory, int sizeInBytes, int offsetInBytes)
	{
		myBufferObject->copyFromSystemMemory(bufferSystemMemory, sizeInBytes, offsetInBytes);
	}

	IndexBufferGL3X::~IndexBufferGL3X()
	{
		delete myBufferObject;
	}
}
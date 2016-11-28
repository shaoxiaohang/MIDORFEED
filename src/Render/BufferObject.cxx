#include <Render/BufferObject.h>

namespace vrv
{
	BufferObject::BufferObject(BufferTarget target, BufferUsage usage, int sizeInBytes)
		: myBufferTarget(target)
		, myBufferUsage(usage)
		, mySizeInBytes(sizeInBytes)
	{
		//empty
	}

	BufferObject::~BufferObject()
	{
		//epmty
	}

	void BufferObject::copyFromSystemMemory(void* bufferSystemMemory, int sizeInBytes)
	{
		copyFromSystemMemory(bufferSystemMemory, sizeInBytes, 0);
	}

	BufferUsage BufferObject::bufferUsage()
	{
		return myBufferUsage;
	}

	int BufferObject::size()
	{
		return mySizeInBytes;
	}
}
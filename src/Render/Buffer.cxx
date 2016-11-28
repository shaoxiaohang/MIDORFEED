#include <Render/Buffer.h>

namespace vrv
{
	Buffer::Buffer(BufferTarget target, BufferUsage usage, int sizeInBytes)
		: myTarget(target)
		, myUsage(usage)
		, mySizeInBytes(sizeInBytes)
	{
		//empty
	}

	void Buffer::copyFromSystemMemory(void* bufferSystemMemory, int sizeInBytes)
	{
		copyFromSystemMemory(bufferSystemMemory, sizeInBytes, 0);
	}

	int Buffer::sizeInBytes()
	{
		return mySizeInBytes;
	}
}
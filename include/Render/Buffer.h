#pragma once

#include<Render/BufferObject.h>
namespace vrv
{
	class Buffer
	{
	public:
		Buffer(BufferTarget target, BufferUsage usage, int sizeInBytes);

		void copyFromSystemMemory(void* bufferSystemMemory, int sizeInBytes);

		virtual void copyFromSystemMemory(void* bufferSystemMemory, int sizeInBytes, int offsetInBytes) = 0;

		int sizeInBytes();

	protected:
		BufferTarget myTarget;
		BufferUsage myUsage;
		int mySizeInBytes;
	};
}
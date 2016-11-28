#pragma once

namespace vrv
{
	enum BufferTarget
	{
		ARRAY_BUFFER,
		ELEMENT_ARRAY_BUFFER
	};

	enum BufferUsage
	{
		STATIC,
		DYNAMIC
	};

	class BufferObject
	{
	public:

		BufferObject(BufferTarget target, BufferUsage usage, int sizeInBytes);

		virtual ~BufferObject();

		void copyFromSystemMemory(void* bufferSystemMemory, int sizeInBytes);

		virtual void copyFromSystemMemory(void* bufferSystemMemory, int sizeInBytes, int offsetInBytes) = 0;

		BufferUsage bufferUsage();

		int size();

	protected:

		BufferTarget myBufferTarget;
		BufferUsage myBufferUsage;
		int mySizeInBytes;
	};
}
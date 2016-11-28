#pragma once
#include <Render/IndexBuffer.h>

namespace vrv
{
	class BufferObjectGL3X;

	class IndexBufferGL3X : public IndexBuffer
	{
	public:
		IndexBufferGL3X(BufferUsage usage, int sizeInBytes);

		void copyFromSystemMemory(void* bufferSystemMemory, int sizeInBytes, int offsetInBytes);

		~IndexBufferGL3X();

	protected:
		BufferObjectGL3X* myBufferObject;
		unsigned myID;
	};
}
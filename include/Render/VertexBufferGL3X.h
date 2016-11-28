#pragma once
#include <Render/VertexBuffer.h>

namespace vrv
{
	class BufferObjectGL3X;

	class VertexBufferGL3X : public VertexBuffer
	{
	public:
		VertexBufferGL3X(BufferUsage usage, int sizeInBytes);

		void copyFromSystemMemory(void* bufferSystemMemory, int sizeInBytes, int offsetInBytes);

		~VertexBufferGL3X();
		
	protected:
		BufferObjectGL3X* myBufferObject;
		unsigned myID;
	};
}
#pragma once

#include<Render/BufferObject.h>
namespace vrv
{
	class BufferObjectGL3X : public BufferObject
	{
	public:
		BufferObjectGL3X(BufferTarget target, BufferUsage usage, int sizeInBytes);

		void copyFromSystemMemory(void* bufferSystemMemory, int sizeInBytes, int offsetInBytes);

		void bind();

		void unBind();

		int typeToGL3X(BufferTarget target);

		int typeToGL3X(BufferUsage usage);

		void deleteBuffer();

		~BufferObjectGL3X();

	protected:
		int myGLBufferTarget;
		int myGLBufferUsage;
		unsigned myID;
	};
}
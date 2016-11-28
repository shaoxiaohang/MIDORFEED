#include<Render/BufferObjectGL3X.h>
#include<GL/glew.h>
namespace vrv
{
	BufferObjectGL3X::BufferObjectGL3X(BufferTarget target, BufferUsage usage, int sizeInBytes)
		: BufferObject(target, usage, sizeInBytes)
		, myGLBufferTarget(typeToGL3X(target))
		, myGLBufferUsage(typeToGL3X(usage))
	{
		glGenBuffers(1, &myID);
		bind();
		glBufferData(myGLBufferTarget, sizeInBytes, 0, myGLBufferUsage);
		unBind();
	}

	BufferObjectGL3X::~BufferObjectGL3X()
	{
		deleteBuffer();
	}

	void BufferObjectGL3X::copyFromSystemMemory(void* bufferSystemMemory, int sizeInBytes, int offsetInBytes)
	{
		bind();
		glBufferSubData(myGLBufferTarget, offsetInBytes, sizeInBytes, bufferSystemMemory);
	}

	void BufferObjectGL3X::deleteBuffer()
	{
		glDeleteBuffers(1, &myID);
	}

	void BufferObjectGL3X::bind()
	{
		glBindBuffer(myGLBufferTarget, myID);
	}

	void BufferObjectGL3X::unBind()
	{
		glBindBuffer(myGLBufferTarget, 0);
	}

	int BufferObjectGL3X::typeToGL3X(BufferTarget target)
	{
		switch (target)
		{
		case ARRAY_BUFFER:
			return GL_ARRAY_BUFFER;
			break;
		case ELEMENT_ARRAY_BUFFER:
			return GL_ELEMENT_ARRAY_BUFFER;
			break;
		default:
			return -1;
			break;
		}
	}

	int BufferObjectGL3X::typeToGL3X(BufferUsage usage)
	{
		switch (usage)
		{
		case STATIC:
			return GL_STATIC_DRAW;
		case DYNAMIC:
			return GL_DYNAMIC_DRAW;
		default:
			return -1;
			break;
		}
	}
}
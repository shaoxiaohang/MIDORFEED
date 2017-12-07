#include <Render/BufferObject.h>
#include <Render/Array.h>
#include <Render/QtContext.h>
namespace vrv
{
	BufferObject::BufferObject(BufferTargetType type, BufferUsage usage)
		: myType(type)
		, myUsage(usage)
	{
		switch (myType)
		{
		case ARRAY_BUFFER:
			myGLType = GL_ARRAY_BUFFER;
			break;
		case ELEMENT_ARRAY_BUFFER:
			myGLType = GL_ELEMENT_ARRAY_BUFFER;
			break;
		case UNIFORM_BUFFER:
			myGLType = GL_UNIFORM_BUFFER;
			break;
		default:
			break;
		}
		switch (myUsage)
		{
		case STATIC_DRAW:
			myGLUsage = GL_STATIC_DRAW;
			break;
		case DYNAMIC_DRAW:
			myGLUsage = GL_DYNAMIC_DRAW;
			break;
		case STREAM_DRAW:
			myGLUsage = GL_STREAM_DRAW;
			break;
		default:
			break;
		}
		QtContext::instance().glGenBuffers(1, &myID);
	}

	BufferObject::~BufferObject()
	{
		QtContext::instance().glDeleteBuffers(1, &myID);
	}

	void BufferObject::copyFromSystemMemory(Array* array)
	{
		bind();
		QtContext::instance().glBufferData(myGLType, array->sizeInBytes(), array->dataPointer(), myGLUsage);
	}

	void BufferObject::bind()
	{
		QtContext::instance().glBindBuffer(myGLType, myID);
	}

	void BufferObject::unbind()
	{
		QtContext::instance().glBindBuffer(myGLType, 0);
	}

	void BufferObject::bufferData(int size, void* data)
	{
		QtContext::instance().glBufferData(myGLType, size, data, myGLUsage);
	}

	void BufferObject::bufferSubData(int offset, int size, void* data)
	{
		QtContext::instance().glBufferSubData(myGLType, offset, size, data);
	}
}
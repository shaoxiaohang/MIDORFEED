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
		case vrv::BufferObject::ARRAY_BUFFER:
			myGLType = GL_ARRAY_BUFFER;
			break;
		case vrv::BufferObject::ELEMENT_ARRAY_BUFFER:
			myGLType = GL_ELEMENT_ARRAY_BUFFER;
			break;
		default:
			break;
		}
		switch (myUsage)
		{
		case vrv::BufferObject::STATIC_DRAW:
			myGLUsage = GL_STATIC_DRAW;
			break;
		case vrv::BufferObject::DYNAMIC_DRAW:
			myGLUsage = GL_DYNAMIC_DRAW;
			break;
		case vrv::BufferObject::STREAM_DRAW:
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

	void BufferObject::copyFromSystemMemory(const Array* array)
	{
		//TODO cache the current bind target id in context
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


}
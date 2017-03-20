#include <Render/BufferObject.h>
#include <Core/Array.h>
#include <GL/glew.h>
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
		glGenBuffers(1, &myID);
	}

	BufferObject::~BufferObject()
	{
		glDeleteBuffers(1, &myID);
	}

	void BufferObject::copyFromSystemMemory(const Array* array)
	{
		//TODO cache the current bind target id in context
		bind();
		glBufferData(myGLType, array->sizeInBytes(), array->dataPointer(), myGLUsage);
	}

	void BufferObject::bind()
	{
		glBindBuffer(myGLType, myID);
	}

	void BufferObject::unbind()
	{
		glBindBuffer(myGLType, 0);
	}


}
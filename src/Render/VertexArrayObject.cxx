#include<Render/VertexArrayObject.h>
#include<Render/BufferObject.h>
#include<Render/VertexBufferObject.h>
#include<Render/IndexBufferObject.h>
#include<Render/VertexAttribute.h>
#include<GL/glew.h>
namespace vrv
{
	VertexArrayObject::VertexArrayObject()
		: myIndexBufferObject(0)
	{
		glGenVertexArrays(1, &myID);
	}
	void VertexArrayObject::bind()
	{
		glBindVertexArray(myID);
	}
	void VertexArrayObject::unbind()
	{
		glBindVertexArray(0);
	}
	void VertexArrayObject::bindVertexAttribute(VertexAttribute* att)
	{
		enableVertexAttribute(att->location());
		glVertexAttribPointer(att->location(), att->count(), att->baseType(), att->normalized(), att->stride(), (GLvoid*)att->offset());
	}
	void VertexArrayObject::enableVertexAttribute(unsigned int i)
	{
		glEnableVertexAttribArray(i);
	}
	void VertexArrayObject::disableVertexAttribute(unsigned int i)
	{
		glDisableVertexAttribArray(i);
	}

	void VertexArrayObject::bindVertexBufferObject(VertexBufferObject* vbo)
	{
		myVertexBufferObjects.push_back(vbo);
		bind();
		vbo->bind();
		VertexBufferObject::VertexAttributesVector::iterator begin = vbo->attributes().begin();
		VertexBufferObject::VertexAttributesVector::iterator end = vbo->attributes().end();
		for (; begin != end; ++begin)
		{
			bindVertexAttribute(*begin);
		}
	}

	void VertexArrayObject::bindIndexBufferObject(IndexBufferObject* ibo)
	{
		myIndexBufferObject = ibo;
		myIndexBufferObject->bind();
	}

	IndexBufferObject* VertexArrayObject::indexBufferObject()
	{
		return myIndexBufferObject;
	}
}
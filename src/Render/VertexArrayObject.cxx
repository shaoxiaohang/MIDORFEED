#include<Render/VertexArrayObject.h>
#include<Render/BufferObject.h>
#include<Render/VertexBufferObject.h>
#include<Render/IndexBufferObject.h>
#include<Render/VertexAttribute.h>
#include<Render/QtContext.h>
namespace vrv
{
	VertexArrayObject::VertexArrayObject()
		: myIndexBufferObject(0)
	{
		QtContext::instance().glGenVertexArrays(1, &myID);
	}
	void VertexArrayObject::bind()
	{
		QtContext::instance().glBindVertexArray(myID);
	}
	void VertexArrayObject::unbind()
	{
		QtContext::instance().glBindVertexArray(0);
	}
	void VertexArrayObject::bindVertexAttribute(VertexAttribute* att)
	{
		enableVertexAttribute(att->location());
		QtContext::instance().glVertexAttribPointer(att->location(), att->count(), att->baseType(), att->normalized(), att->stride(), (GLvoid*)att->offset());
	}
	void VertexArrayObject::enableVertexAttribute(unsigned int i)
	{
		QtContext::instance().glEnableVertexAttribArray(i);
	}
	void VertexArrayObject::disableVertexAttribute(unsigned int i)
	{
		QtContext::instance().glDisableVertexAttribArray(i);
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
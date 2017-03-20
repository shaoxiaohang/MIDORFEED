#include<Render/VertexArrayObject.h>
#include<Render/BufferObject.h>
#include<Render/VertexAttribute.h>
#include<GL/glew.h>
namespace vrv
{
	VertexArrayObject::VertexArrayObject()
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
		bind();
		glEnableVertexAttribArray(i);
		unbind();
	}
	void VertexArrayObject::disableVertexAttribute(unsigned int i)
	{
		bind();
		glDisableVertexAttribArray(i);
		unbind();
	}

	void VertexArrayObject::bindVertexBufferObject(VertexBufferObject* vbo)
	{
		myVertexBufferObjects.push_back(vbo);
		vbo->bindVAO(this);
	}
}
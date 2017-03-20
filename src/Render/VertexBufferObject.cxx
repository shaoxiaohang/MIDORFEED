#include<Render/VertexBufferObject.h>
#include<Render/VertexArrayObject.h>
namespace vrv
{
	VertexBufferObject::VertexBufferObject(BufferUsage usage)
		: BufferObject(BufferObject::ARRAY_BUFFER, usage)
	{}

	void VertexBufferObject::addVertexAttribute(VertexAttribute* vertexAttri)
	{
		myAttributes.push_back(vertexAttri);
	}

	void VertexBufferObject::bindVAO(VertexArrayObject* vao)
	{
		vao->bind();
		bind();
		VertexAttributesVector::iterator begin = myAttributes.begin();
		VertexAttributesVector::iterator end = myAttributes.end();
		for (; begin != end; ++begin)
		{
			vao->bindVertexAttribute(*begin);
		}
		unbind();
		vao->unbind();
	}
}
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

	VertexBufferObject::VertexAttributesVector& VertexBufferObject::attributes()
	{
		return myAttributes;
	}
}
#pragma once
#include <Render/BufferObject.h>
#include <vector>

namespace vrv
{
	class VertexAttribute;
	class VertexArrayObject;
	class VertexBufferObject : public BufferObject
	{
	public:
		typedef std::vector<VertexAttribute*> VertexAttributesVector;
		VertexBufferObject(BufferUsage usage = BufferObject::STATIC_DRAW);
		void addVertexAttribute(VertexAttribute* vertexAttri);
		//feed all the vertex attributes in this VBO to VAO
		void bindVAO(VertexArrayObject* vao);
	protected:
		VertexAttributesVector myAttributes;
	};
}
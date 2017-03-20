#pragma once
#include<Render/VertexBufferObject.h>
#include<vector>
namespace vrv
{
	class VertexBufferObject;
	class VertexAttribute;
	class VertexArrayObject
	{
	public:
		VertexArrayObject();
		void bind();
		void unbind();
		void bindVertexAttribute(VertexAttribute* att);
		void enableVertexAttribute(unsigned int i);
		void disableVertexAttribute(unsigned int i);
		void bindVertexBufferObject(VertexBufferObject* vbo);
	protected:
		unsigned int myID;
		std::vector<VertexBufferObject*> myVertexBufferObjects;
	};
}
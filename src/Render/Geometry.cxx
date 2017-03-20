#include<Render/Geometry.h>
#include<Render/VertexArrayObject.h>
#include<Render/VertexAttribute.h>
#include<Render/VertexBufferObject.h>
#include<Render/Scene.h>
namespace vrv
{
	Geometry::Geometry()
		: Drawable()
		, myVertexArray(0)
		, myNormalArray(0)
		, myNormalBinding(PerVertex)
		, myIndexArray(0)
	{}

	void Geometry::setVertexArray(Array* array)
	{
		myVertexArray = array;
	}

	void Geometry::setNomralArray(Array* array, VertexBinding binding)
	{
		myNormalArray = array;
		myNormalBinding = binding;
	}

	void Geometry::setIndexArray(Array* array)
	{
		myIndexArray = array;
	}

	void Geometry::buildGeometry()
	{
		if (!myBuildGeometry)
		{
			VertexArrayObject* vao = new VertexArrayObject();
			VertexBufferObject* vbo = new VertexBufferObject();
			if (myIndexArray)
			{
				
			}
		}
	}
}
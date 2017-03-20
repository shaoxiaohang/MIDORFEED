#include<Render/Geometry.h>
#include<Render/VertexArrayObject.h>
#include<Render/VertexAttribute.h>
#include<Render/VertexBufferObject.h>
#include<Render/Scene.h>
namespace vrv
{
	Geometry::Geometry()
		: myVertexArray(0)
		, myNormalArray(0)
		, myNormalBinding(PerVertex)
		, myIndexArray(0)
	{}

	void Geometry::setVertexArray(Array* array)
	{
		myVertexArray = array;
		VertexArrayObject* vao = new VertexArrayObject();
		VertexBufferObject* vbo = new VertexBufferObject();
		vbo->copyFromSystemMemory(array);
		vbo->addVertexAttribute(new VertexAttributeVector3f("pos",Geometry::VertexAttLocation::POSITION));
		vao->bindVertexBufferObject(vbo);
		createDrawState(vao, Scene::instance().defaultProgram());
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
}
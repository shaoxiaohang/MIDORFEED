#include <Render/Geometry.h>
#include <Render/VertexArrayObject.h>
#include <Render/VertexAttribute.h>
#include <Render/VertexBufferObject.h>
#include <Render/IndexBufferObject.h>
#include <Render/Scene.h>
#include <Render/Uniform.h>
#include <Render/Program.h>
#include <Render/QtContext.h>
#include <Render/Texture.h>
#include <Render/Material.h>
#include <Render/ShaderManager.h>

namespace vrv
{
	Geometry::Geometry()
		: Drawable()
		, myVertexArray(0)
		, myNormalArray(0)
		, myIndexArray(0)
		, myTextureCoordinateArray(0)
	{}

	void Geometry::setVertex(ArrayVec3* array)
	{
		myVertexArray = new ArrayVec3(array);
	}

	void Geometry::setNomral(ArrayVec3* array)
	{
		myNormalArray = new ArrayVec3(array);
	}

	void Geometry::setIndex(ArrayUnsignedInt* array)
	{
		myIndexArray = new ArrayUnsignedInt(array);
		addPrimitiveSet(Drawable::TRIANGLES, array->size(), Array::UNSIGNED_INT);
	}

	void Geometry::setTextureCoordinate(ArrayVec2* array)
	{
		myTextureCoordinateArray = new ArrayVec2(array);
	}

	void Geometry::buildGeometry(Material* material)
	{
		if (!myBuildGeometry)
		{
			VertexArrayObject* vao = new VertexArrayObject();
			VertexBufferObject* vbo_pos = new VertexBufferObject();
			vbo_pos->addVertexAttribute(new VertexAttributeVector3f("pos", 0));
			vbo_pos->copyFromSystemMemory(myVertexArray);
			vao->bindVertexBufferObject(vbo_pos);
			if (myIndexArray)
			{
				IndexBufferObject* ibo = new IndexBufferObject();
				ibo->copyFromSystemMemory(myIndexArray);
				vao->bindIndexBufferObject(ibo);
			}
			if (myTextureCoordinateArray)
			{
				VertexBufferObject* vbo_st = new VertexBufferObject();
				vbo_st->addVertexAttribute(new VertexAttributeVector2f("st", 1));
				vbo_st->copyFromSystemMemory(myTextureCoordinateArray);
				vao->bindVertexBufferObject(vbo_st);
			}
			if (myNormalArray)
			{
				VertexBufferObject* vbo_normal = new VertexBufferObject();
				vbo_normal->addVertexAttribute(new VertexAttributeVector3f("normal", 2));
				vbo_normal->copyFromSystemMemory(myNormalArray);
				vao->bindVertexBufferObject(vbo_normal);
			}
			Program* phoneLighting = ShaderManager::instance().getProgram(ShaderManager::PhoneLighting);
			createDrawState(vao, phoneLighting);
			myBuildGeometry = true;
		}
	}
}
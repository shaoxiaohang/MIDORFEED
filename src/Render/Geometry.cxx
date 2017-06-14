#include<Render/Geometry.h>
#include<Render/VertexArrayObject.h>
#include<Render/VertexAttribute.h>
#include<Render/VertexBufferObject.h>
#include<Render/IndexBufferObject.h>
#include<Render/Scene.h>
#include<Render/Uniform.h>
#include<Render/Program.h>
#include<Render/QtContext.h>
#include<Render/Texture2D.h>
namespace vrv
{
	Geometry::Geometry()
		: Drawable()
		, myVertexArray(0)
		, myNormalArray(0)
		, myNormalBinding(PerVertex)
		, myIndexArray(0)
	{}

	void Geometry::setVertex(Array* array)
	{
		myVertexArray = array;
	}

	void Geometry::setNomral(Array* array, VertexBinding binding)
	{
		myNormalArray = array;
		myNormalBinding = binding;
	}

	void Geometry::setIndex(Array* array)
	{
		myIndexArray = array;
	}

	void Geometry::setTextureCoordinate(Array* array)
	{
		myTextureCoordinateArray = array;
	}

	void Geometry::setTexture2D(Texture2D* texture, unsigned int i)
	{
		myTextureMap[i] = texture;
	}

	void Geometry::buildGeometry()
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
			Program* defaultProgram = Scene::instance().defaultProgram();
			for (int i = 0; i < myTextureMap.size(); i++)
			{
				QtContext::instance().glActiveTexture(GL_TEXTURE0 + i);
				QtContext::instance().glBindTexture(GL_TEXTURE_2D, myTextureMap[i]->id());
				std::string samplerName = "texture" + std::to_string(i);
				Uniform* uniform = defaultProgram->getUniform(samplerName);
				if (uniform)
				{
					uniform->set(i);
				}
			}
			createDrawState(vao, defaultProgram);
			myBuildGeometry = true;
		}
	}
}
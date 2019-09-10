#include <Render/Geometry.h>
#include <Render/VertexArrayObject.h>
#include <Render/VertexAttribute.h>
#include <Render/VertexBufferObject.h>
#include <Render/IndexBufferObject.h>
#include <Render/Scene.h>
#include <Render/Uniform.h>
#include <Render/Program.h>
#include <Render/Texture.h>
#include <Render/Material.h>
#include <Render/OpenGLContext.h>

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

namespace vrv
{
	Geometry::Geometry()
		: Drawable()
		, myVertexArray(0)
		, myNormalArray(0)
		, myTangentArray(0)
		, myIndexArray(0)
		, myTextureCoordinateArray(0)
		, myInstancedArray(0)
		, myBuildNormal(false)
		, myBuildTangent(false)
	{}

	void Geometry::setVertex(ArrayVec3* array)
	{
		myVertexArray = array;
	}

	void Geometry::setVertex(ArrayVec2* array)
	{
		myVertexArray = new ArrayVec3(array);
	}

	void Geometry::setNomral(ArrayVec3* array)
	{
		myNormalArray = array;
	}

	void Geometry::setTangent(ArrayVec3* array)
	{
		myTangentArray = array;
	}

	void Geometry::setIndex(ArrayUnsignedInt* array)
	{
		myIndexArray = array;
		addPrimitiveSet(Drawable::TRIANGLES, array->size(), Array::UNSIGNED_INT);
	}

	void Geometry::setTextureCoordinate(ArrayVec2* array)
	{
		myTextureCoordinateArray = array;
	}

	void Geometry::setInstancedMatrices(ArrayVec3* array)
	{
		myIsInstanced = true;
		myInstancedArray = array;
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

			if (!myNormalArray && myBuildNormal)
			{
				calculateNormal();
			}

			if (myNormalArray)
			{
				VertexBufferObject* vbo_normal = new VertexBufferObject();
				vbo_normal->addVertexAttribute(new VertexAttributeVector3f("normal", 2));
				vbo_normal->copyFromSystemMemory(myNormalArray);
				vao->bindVertexBufferObject(vbo_normal);
			}

			if (!myTangentArray && myBuildTangent)
			{
				calculateTangent();
			}

			if (myTangentArray)
			{
				VertexBufferObject* vbo_tangent = new VertexBufferObject();
				vbo_tangent->addVertexAttribute(new VertexAttributeVector3f("tangent", 3));
				vbo_tangent->copyFromSystemMemory(myTangentArray);
				vao->bindVertexBufferObject(vbo_tangent);
			}

			if (myInstancedArray)
			{
				VertexBufferObject* vbo_instanced = new VertexBufferObject();
				vbo_instanced->addVertexAttribute(new VertexAttributeVector3f("instancedMatrix", 4));
				vbo_instanced->copyFromSystemMemory(myInstancedArray);
				vao->bindVertexBufferObject(vbo_instanced);
            OpenGLContext::instance().glVertexAttribDivisor(4, 1);
			}

			setVertexArrayObject(vao);

         calculateBound();
			myBuildGeometry = true;
		}
	}

	void Geometry::setBuildNormal(bool b)
	{
		myBuildNormal = b;
	}

	void Geometry::setBuildTangent(bool b)
	{
		myBuildTangent = b;
	}

	void Geometry::calculateNormal()
	{
		int vertexSize;

		if (myIndexArray)
		{
			vertexSize = myIndexArray->size();
		}
		else
		{
			vertexSize = myVertexArray->size();
		}

		ArrayVec3* normals = new ArrayVec3(vertexSize);

		for (int i=0 ; i < vertexSize; i += 3)
		{
			Vector3f i0;
			Vector3f i1;
			Vector3f i2;

			if (myIndexArray)
			{
				int index0 = myIndexArray->get(i);
				int index1 = myIndexArray->get(i + 1);
				int index2 = myIndexArray->get(i + 2);

				i0 = myVertexArray->get(index0);
				i1 = myVertexArray->get(index1);
				i2 = myVertexArray->get(index2);
			}
			else
			{
				i0 = myVertexArray->get(i);
				i1 = myVertexArray->get(i + 1);
				i2 = myVertexArray->get(i + 2);
			}

			Vector3f E1 = i1 - i0;
			Vector3f E2 = i2 - i0;

			Vector3f normal = E1.crossProduct(E2).normalizedVector();
			normals->set(i, normal);
			normals->set(i + 1, normal);
			normals->set(i + 2, normal);
		}

		setNomral(normals);
	}

	void Geometry::calculateTangent()
	{	
		int vertexSize;

		if (myIndexArray)
		{
			vertexSize = myIndexArray->size();
		}
		else
		{
			vertexSize = myVertexArray->size();
		}

		ArrayVec3* tangents = new ArrayVec3(vertexSize);

		for (int i = 0; i < vertexSize; i += 3)
		{
			Vector3f i0;
			Vector3f i1;
			Vector3f i2;
			Vector2f st0;
			Vector2f st1;
			Vector2f st2;

			if (myIndexArray)
			{
				int index0 = myIndexArray->get(i);
				int index1 = myIndexArray->get(i + 1);
				int index2 = myIndexArray->get(i + 2);

				i0 = myVertexArray->get(index0);
				i1 = myVertexArray->get(index1);
				i2 = myVertexArray->get(index2);

				st0 = myTextureCoordinateArray->get(index0);
				st1 = myTextureCoordinateArray->get(index1);
				st2 = myTextureCoordinateArray->get(index2);
			}
			else
			{
				i0 = myVertexArray->get(i);
				i1 = myVertexArray->get(i + 1);
				i2 = myVertexArray->get(i + 2);
				
				st0 = myTextureCoordinateArray->get(i);
				st1 = myTextureCoordinateArray->get(i + 1);
				st2 = myTextureCoordinateArray->get(i + 2);
			}



			Vector3f E1 = i1 - i0;
			Vector3f E2 = i2 - i0;

			float deltaU1 = st1.x() - st0.x();
			float deltaV1 = st1.y() - st0.y();
			float deltaU2 = st2.x() - st0.x();
			float deltaV2 = st2.y() - st0.y();


			float f = 1.0 / (deltaU1*deltaV2 - deltaU2*deltaV1);

			Vector3f tangent;
			tangent.x() = f*(deltaV2*E1.x() - deltaV1*E2.x());
			tangent.y() = f*(deltaV2*E1.y() - deltaV1*E2.y());
			tangent.z() = f*(deltaV2*E1.z() - deltaV1*E2.z());

			tangent = tangent.normalizedVector();

			tangents->add(tangent);
			tangents->add(tangent);
			tangents->add(tangent);
		}

		setTangent(tangents);
	}

   void Geometry::calculateBound()
   {
      int vertexSize;

      if (myIndexArray)
      {
         vertexSize = myIndexArray->size();
      }
      else
      {
         vertexSize = myVertexArray->size();
      }

      Vector3f minV(FLT_MAX, FLT_MAX, FLT_MAX);
      Vector3f maxV(FLT_MIN, FLT_MIN, FLT_MIN);
      for (int i = 0; i < vertexSize; i++)
      {
         Vector3f vertex;
         if (myIndexArray)
         {
            int index = myIndexArray->get(i);
            vertex = myVertexArray->get(index);
         }
         else
         {
            vertex = myVertexArray->get(i);
         }

         minV.x() = std::min(minV.x(), vertex.x());
         minV.y() = std::min(minV.y(), vertex.y());
         minV.z() = std::min(minV.z(), vertex.z());
         maxV.x() = std::max(maxV.x(), vertex.x());
         maxV.y() = std::max(maxV.y(), vertex.y());
         maxV.z() = std::max(maxV.z(), vertex.z());
      }

      myBound.setMinVector(minV);
      myBound.setMaxVector(maxV);
   }
}
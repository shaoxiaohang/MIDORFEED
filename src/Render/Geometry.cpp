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

namespace vrv
{
	Geometry::Geometry()
		: Drawable()
	{

   }

   void Geometry::addVertexAttribute(unsigned int pos, Array* array)
   {
      VertexBufferObject* vbo = new VertexBufferObject();
      Array::DataType dataType = array->dataType();
      VertexAttribute* attribute = 0;
      switch (dataType)
      {
      case Array::INT:
         attribute = new VertexAttributeInt(pos);
         break;
      case Array::FLOAT:
         attribute = new VertexAttributefloat(pos);
         break;
      case Array::VEC2F:
         attribute = new VertexAttributeVector2f(pos);
         break;
      case Array::VEC3F:
         attribute = new VertexAttributeVector3f(pos);
         break;
      case Array::VEC4F:
         attribute = new VertexAttributeVector4f(pos);
         break;
      default:
         break;
      }

      if (attribute)
      {
         vbo->addVertexAttribute(attribute);
         vbo->copyFromSystemMemory(array);
         myVertexArrayObject->bindVertexBufferObject(vbo);
      }     
   }

   void Geometry::addVertexIndex(Array* array)
   {
      IndexBufferObject* ibo = new IndexBufferObject();
      ibo->copyFromSystemMemory(array);
      myVertexArrayObject->bindIndexBufferObject(ibo);
   }
}
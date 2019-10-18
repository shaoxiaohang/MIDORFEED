#include <Render/Drawable.h>
#include <Render/StateSet.h>
#include <Render/Program.h>
#include <Render/VertexArrayObject.h>
#include <Render/Material.h>
#include <Render/RenderState.h>
#include <Render/OpenGLContext.h>

namespace vrv
{
	Drawable::PrimitiveSet::PrimitiveSet(Primitive pri, unsigned int start, unsigned int count)
		: myPrimitive(pri)
		, myStart(start)
		, myCount(count)
		, myGLIndexType(0)
		, myRenderApproach(DRAW_ARRAYS)
	{
		mapToGLPrimitiveType();
	}

	Drawable::PrimitiveSet::PrimitiveSet(Primitive pri, unsigned int count, IndexType type)
		: myPrimitive(pri)
		, myCount(count)
		, myIndexType(type)
		, myRenderApproach(DRAW_ELEMENTS)
	{
		mapToGLPrimitiveType();
		mapToGLIndexType();
	}

	void Drawable::PrimitiveSet::mapToGLPrimitiveType()
	{
		switch (myPrimitive)
		{
		case vrv::Drawable::POINTS:
			myGLPrimitiveType = GL_POINTS;
			break;
		case vrv::Drawable::LINES:
			myGLPrimitiveType = GL_LINES;
			break;
		case vrv::Drawable::TRIANGLES:
			myGLPrimitiveType = GL_TRIANGLES;
			break;
		case vrv::Drawable::QUADS:
			myGLPrimitiveType = GL_QUADS;
			break;
		default:
			break;
		}
	}

	void Drawable::PrimitiveSet::mapToGLIndexType()
	{
		switch (myIndexType)
		{
		case vrv::Drawable::PrimitiveSet::UNSIGNED_BYTE:
			myGLIndexType = GL_UNSIGNED_BYTE;
			break;
		case vrv::Drawable::PrimitiveSet::UNSIGNED_SHORT:
			myGLIndexType = GL_UNSIGNED_SHORT;
			break;
		case vrv::Drawable::PrimitiveSet::UNSIGNED_INT:
			myGLIndexType = GL_UNSIGNED_INT;
			break;
		default:
			break;
		}
	}

	Drawable::Drawable()
		: myMaterial(0)
		, myIsInstanced(false)
		, myInstancedCount(0)
		, myVertexArrayObject(0)
	{
      myMaterial = new Material();
      myVertexArrayObject = new VertexArrayObject();
   }

	void Drawable::drawImplementation()
	{
      if (myMaterial)
      {
         StateSet* stateSet = myMaterial->stateSet();
         if (stateSet)
         {
            stateSet->bind();
            stateSet->program()->updateUniforms();
            stateSet->renderState()->apply();
            myVertexArrayObject->bind();
            for (unsigned int i = 0; i < myPrimitiveSets.size(); ++i)
            {
               const PrimitiveSet& set = myPrimitiveSets[i];
               switch (set.myRenderApproach)
               {
               case PrimitiveSet::DRAW_ARRAYS:
                  if (myIsInstanced)
                  {
                     OpenGLContext::instance().glDrawArraysInstanced(myPrimitiveSets[i].myGLPrimitiveType,
                        myPrimitiveSets[i].myStart, myPrimitiveSets[i].myCount, myInstancedCount);
                  }
                  else
                  {
                     glDrawArrays(myPrimitiveSets[i].myGLPrimitiveType,
                        myPrimitiveSets[i].myStart, myPrimitiveSets[i].myCount);
                  }
                  break;
               case PrimitiveSet::DRAW_ELEMENTS:
                  if (myIsInstanced)
                  {
                     OpenGLContext::instance().glDrawElementsInstanced(myPrimitiveSets[i].myGLPrimitiveType,
                        myPrimitiveSets[i].myCount, myPrimitiveSets[i].myGLIndexType, 0, myInstancedCount);
                  }
                  else
                  {
                     glDrawElements(myPrimitiveSets[i].myGLPrimitiveType,
                        myPrimitiveSets[i].myCount, myPrimitiveSets[i].myGLIndexType, 0);
                  }
                  break;
               default:
                  break;
               }

            }

            stateSet->unbind();
            myVertexArrayObject->unbind();
         }
      }
		
	}
	
	void Drawable::addPrimitiveSet(Primitive pri, unsigned int start, unsigned int cout)
	{
		myPrimitiveSets.push_back(PrimitiveSet(pri, start, cout));
	}

	void Drawable::addPrimitiveSet(Primitive pri, unsigned int cout, Array::DataType indexType)
	{
		PrimitiveSet::IndexType type;
		switch (indexType)
		{
		case vrv::Array::INT:
		case vrv::Array::UNSIGNED_INT:
			type = PrimitiveSet::IndexType::UNSIGNED_INT;
			break;
		default:
			break;
		}
		myPrimitiveSets.push_back(PrimitiveSet(pri, cout, type));
	}

	void Drawable::setVertexArrayObject(VertexArrayObject* vao)
	{
		myVertexArrayObject = vao;
	}

	void Drawable::setMaterial(Material* material)
	{
		myMaterial = material;
	}

	Material* Drawable::material()
	{
		return myMaterial;
	}
	
	void Drawable::setInstancedCount(int count)
	{
		myInstancedCount = count;
		myIsInstanced = true;
	}

	bool Drawable::instanced()
	{
		return myIsInstanced;
	}

	void Drawable::updateProgram()
	{
      if (myMaterial)
      {
         StateSet* state = myMaterial->stateSet();
         if (state)
         {
            Program* program = state->program();
            if (program)
            {
               program->set("vrv_instanced", myIsInstanced);
            }
         }
         myMaterial->updateProgram();
      }

	}

	Material* Drawable::getOrCreateMaterial()
	{
		if (!myMaterial)
		{
			myMaterial = new Material();
		}
		return myMaterial;
	}

   Bound Drawable::bound()
   {
      return myBound;
   }

}

#include <Render/Drawable.h>
#include <Render/DrawState.h>
#include <Render/Program.h>
#include <Render/VertexArrayObject.h>
#include <GL/glew.h>
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

	DrawState* Drawable::drawState()
	{
		return myDrawState;
	}

	const DrawState* Drawable::drawState() const
	{
		return myDrawState;
	}

	void Drawable::drawImplementation()
	{
		if (myBuildGeometry == false)
		{
			buildGeometry();
			myBuildGeometry = true;
		}
		myDrawState->bind();
		for (unsigned int i = 0; i < myPrimitiveSets.size();++i)
		{
			const PrimitiveSet& set = myPrimitiveSets[i];
			switch (set.myRenderApproach)
			{
			case PrimitiveSet::DRAW_ARRAYS:
				glDrawArrays(myPrimitiveSets[i].myGLPrimitiveType, myPrimitiveSets[i].myStart, myPrimitiveSets[i].myCount);
				break;
			case PrimitiveSet::DRAW_ELEMENTS:
				glDrawElements(myPrimitiveSets[i].myGLPrimitiveType, myPrimitiveSets[i].myCount, myPrimitiveSets[i].myGLIndexType,0);
				break;
			default:
				break;
			}
		
		}
		myDrawState->unbind();
	}
	
	void Drawable::addPrimitiveSet(Primitive pri, unsigned int start, unsigned int cout)
	{
		myPrimitiveSets.push_back(PrimitiveSet(pri, start, cout));
	}

	void Drawable::addPrimitiveSet(Primitive pri, unsigned int cout, PrimitiveSet::IndexType indexType)
	{
		myPrimitiveSets.push_back(PrimitiveSet(pri, cout, indexType));
	}

	void Drawable::createDrawState(VertexArrayObject* vao, Program* shader)
	{
		myDrawState = new DrawState(vao, shader);
	}

	bool Drawable::SortDrawable::operator()(const Drawable* left, const Drawable* right)
	{
		return *(left->drawState()) < *(right->drawState());
	}
	
}

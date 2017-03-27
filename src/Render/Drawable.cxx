#include <Render/Drawable.h>
#include <Render/DrawState.h>
#include <Render/Program.h>
#include <Render/VertexArrayObject.h>
#include <Render/QtContext.h>
#ifdef DrawState
#undef DrawState
#endif
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
		: myBuildGeometry(false)
		, myDrawState(0)
	{}

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
		myDrawState->bind();
		for (unsigned int i = 0; i < myPrimitiveSets.size();++i)
		{
			const PrimitiveSet& set = myPrimitiveSets[i];
			switch (set.myRenderApproach)
			{
			case PrimitiveSet::DRAW_ARRAYS:
				QtContext::instance().glDrawArrays(myPrimitiveSets[i].myGLPrimitiveType, myPrimitiveSets[i].myStart, myPrimitiveSets[i].myCount);
				break;
			case PrimitiveSet::DRAW_ELEMENTS:
				QtContext::instance().glDrawElements(myPrimitiveSets[i].myGLPrimitiveType, myPrimitiveSets[i].myCount, myPrimitiveSets[i].myGLIndexType, 0);
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

	void Drawable::addPrimitiveSet(Primitive pri, unsigned int cout, Array::DataType indexType)
	{
		PrimitiveSet::IndexType type;
		switch (indexType)
		{
		case vrv::Array::INT:
		case vrv::Array::UNSIGNED_INT:
			type = PrimitiveSet::IndexType::UNSIGNED_INT;
			break;
		case vrv::Array::FLOAT:
			break;
		case vrv::Array::VEC2F:
			break;
		case vrv::Array::VEC3F:
			break;
		case vrv::Array::VEC4F:
			break;
		case vrv::Array::MAT3F:
			break;
		case vrv::Array::MAT4F:
			break;
		default:
			break;
		}
		myPrimitiveSets.push_back(PrimitiveSet(pri, cout, type));
	}

	void Drawable::buildGeometryIfNeeded()
	{
		if (!myBuildGeometry)
		{
			buildGeometry();
		}
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

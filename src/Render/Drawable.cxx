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
	{
		switch (myPrimitive)
		{
		case vrv::Drawable::POINTS:
			myGLType = GL_POINTS;
			break;
		case vrv::Drawable::LINES:
			myGLType = GL_LINES;
			break;
		case vrv::Drawable::TRIANGLES:
			myGLType = GL_TRIANGLES;
			break;
		case vrv::Drawable::QUADS:
			myGLType = GL_QUADS;
			break;
		default:
			break;
		}
	}


	Drawable::Drawable()
		: myDrawState(0)
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
			glDrawArrays(myPrimitiveSets[i].myGLType, myPrimitiveSets[i].myStart, myPrimitiveSets[i].myCount);
		}
		myDrawState->unbind();
	}
	
	void Drawable::addPrimitiveSet(Primitive pri, unsigned int start, unsigned int cout)
	{
		myPrimitiveSets.push_back(PrimitiveSet(pri, start, cout));
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

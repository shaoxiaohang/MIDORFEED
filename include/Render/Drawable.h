#pragma once
#include <vector>
namespace vrv
{
	class DrawState;
	class VertexArrayObject;
	class Program;
	class Array;

	class Drawable
	{
	public:
		enum Primitive
		{
			POINTS,
			LINES,
			TRIANGLES,
			QUADS
		};
		struct PrimitiveSet
		{
			PrimitiveSet(Primitive pri, unsigned int start, unsigned int count);
			Primitive myPrimitive;
			unsigned int myStart;
			unsigned int myCount;
			unsigned int myGLType;
		};
	public:
		Drawable();
		DrawState* drawState();
		const DrawState* drawState() const;
		virtual void drawImplementation();
		void addPrimitiveSet(Primitive pri, unsigned int start, unsigned int cout);
		struct SortDrawable
		{
			bool operator()(const Drawable* left, const Drawable* right);
		};
	protected:
		void createDrawState(VertexArrayObject* vao, Program* shader);
	protected:
		DrawState* myDrawState;
		std::vector<PrimitiveSet> myPrimitiveSets;
	};
}
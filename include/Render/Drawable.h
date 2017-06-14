#pragma once
#include <vector>
#include <Render/Array.h>
namespace vrv
{
	class DrawState;
	class VertexArrayObject;
	class Program;
	class Array;

	class Drawable
	{
	public:
		Drawable();
		enum Primitive
		{
			POINTS,
			LINES,
			TRIANGLES,
			QUADS
		};
		struct PrimitiveSet
		{
			enum RenderApproach
			{
				DRAW_ARRAYS,
				DRAW_ELEMENTS
			};
			enum IndexType
			{
				UNSIGNED_BYTE,
				UNSIGNED_SHORT,
				UNSIGNED_INT
			};
			PrimitiveSet(Primitive pri, unsigned int start, unsigned int count);
			PrimitiveSet(Primitive pri, unsigned int count, IndexType type = UNSIGNED_INT);
			Primitive myPrimitive;
			unsigned int myStart;
			unsigned int myCount;
			unsigned int myGLPrimitiveType;
			IndexType myIndexType;
			unsigned int myGLIndexType;
			RenderApproach myRenderApproach;
			void mapToGLPrimitiveType();
			void mapToGLIndexType();
		};
	public:
		DrawState* drawState();
		const DrawState* drawState() const;	
		virtual void drawImplementation();
		void addPrimitiveSet(Primitive pri, unsigned int start, unsigned int cout);
		void addPrimitiveSet(Primitive pri, unsigned int cout, Array::DataType indexType);
		virtual void buildGeometryIfNeeded();
	protected:
		void createDrawState(VertexArrayObject* vao, Program* shader);
		virtual void buildGeometry() = 0;
	protected:
		bool myBuildGeometry;
		DrawState* myDrawState;
		std::vector<PrimitiveSet> myPrimitiveSets;
	};
}
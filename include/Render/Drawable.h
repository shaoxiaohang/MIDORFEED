#pragma once
#include <vector>
#include <Render/Array.h>
#include <Render/Node.h>
#include <Core/Bound.h>
namespace vrv
{
	class DrawState;
	class VertexArrayObject;
	class Program;
	class Array;
	class RenderState;
	class Material;

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
		virtual void drawImplementation(DrawState*);
		void addPrimitiveSet(Primitive pri, unsigned int start, unsigned int cout);
		void addPrimitiveSet(Primitive pri, unsigned int cout, Array::DataType indexType = Array::UNSIGNED_INT);
		virtual void buildGeometryIfNeeded();
		void setVertexArrayObject(VertexArrayObject* vao);
		void setMaterial(Material*);
		Material* material();
		void setInstancedCount(int);
		bool instanced();
		void updateProgram(Program* program);
		Material* getOrCreateMaterial();
      virtual void calculateBound() = 0;
	protected:
		virtual void buildGeometry() = 0;
	protected:
		bool myBuildGeometry;
		VertexArrayObject* myVertexArrayObject;
		std::vector<PrimitiveSet> myPrimitiveSets;
		Material* myMaterial;
		bool myIsInstanced;
		int myInstancedCount;
      Bound myBound;
	};
}
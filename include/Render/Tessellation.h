#pragma once
#include <Core/Vector3.h>
#include <Render/Ellipsoid.h>
namespace vrv
{
	class ArrayVec3;
	class ArrayVec2;
	class ArrayUnsignedInt;
	class Vector3f;
	class Geometry;
	class SubdivisionSphereTessellatorSimple
	{
	public:
		static void compute(ArrayVec3& positions,ArrayUnsignedInt& indexes, int numberOfSubdivisions);

	protected:
		static int numberOfVertices(int numberOfSubdivisions);
		static int numberOfTriangles(int numberOfSubdivisions);
		static void subdivide(ArrayVec3& positions, ArrayUnsignedInt& indexes, Vector3f currenctFace,
			int numberOfSubdivisions);

	protected:
		float myP0;
		float myP1;
		float myP2;
		float myP3;
	};

	class GeographicGridTessellation
	{
	public:
		static void compute(ArrayVec3& position, ArrayUnsignedInt& indexes, ArrayVec3& normal,
			ArrayVec2& st, int numberOfStacks, int numberOfSlices, float a, float b, float c);

	protected:
		static int numberOfVertices(int numberOfStacks, int numberOfSlices);
		static int numberOfTriangles(int numberOfStacks, int numberOfSlices);

	};
}
#pragma once
#include <Render/Geometry.h>
#include <Render/Array.h>
namespace vrv
{
	class Cube : public Geometry
	{
	public:
		Cube();

	protected:
		static bool myGeometryInitialized;
		static ArrayVec3 sPosArray;
		static ArrayVec2 sTexArray;
		static ArrayVec3 sNormalArray;
	};

	class Sphere : public Geometry
	{
	public:
		Sphere();

	protected:
		static bool myGeometryInitialized;
		static ArrayVec3 sPosArray;
		static ArrayUnsignedInt sIndexArray;
		static ArrayVec2 sTexArray;
		static ArrayVec3 sNormalArray;
	};

	class Floor : public Geometry
	{
	public:
		Floor();

	protected:
		static bool myGeometryInitialized;
		static ArrayVec3 sPosArray;
		static ArrayVec2 sTexArray;
		static ArrayVec3 sNormalArray;
	};

	class Billboard : public Geometry
	{
	public:
		Billboard();

	protected:
		static bool myGeometryInitialized;
		static ArrayVec3 sPosArray;
		static ArrayVec2 sTexArray;
		static ArrayVec3 sNormalArray;
	};
}
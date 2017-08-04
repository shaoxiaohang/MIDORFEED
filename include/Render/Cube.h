#pragma once
#include <Render/Mesh.h>
#include <Render/Array.h>
namespace vrv
{
	class Cube : public Mesh
	{
	public:
		Cube();

	protected:
		static bool myGeometryInitialized;
		static ArrayVec3 sPosArray;
		static ArrayVec2 sTexArray;
		static ArrayVec3 sNormalArray;
	};

	class Floor : public Mesh
	{
	public:
		Floor();

	protected:
		static bool myGeometryInitialized;
		static ArrayVec3 sPosArray;
		static ArrayVec2 sTexArray;
		static ArrayVec3 sNormalArray;
	};

	class Billboard : public Mesh
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
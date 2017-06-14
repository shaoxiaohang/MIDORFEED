#pragma once
#include <Render/Geometry.h>
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
}
#pragma once
#include <Core/Vector3.h>
namespace vrv
{
	class Material
	{
	public:
		Material();

	protected:
		Vector3f myAmbient;
		Vector3f myDiffuse;
		Vector3f mySpecular;
		float myShininess;
	};
}
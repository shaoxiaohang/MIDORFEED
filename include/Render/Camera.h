#pragma once
#include <Core/Vector3.h>
#include <Core/Matrix4.h>
namespace vrv
{
	class Camera
	{
	public:
		Camera();
	protected:
		Vector3f myPosition;
		Vector3f myUp;
		Vector3f myRight;
		Vector3f myDirection;
	};
}
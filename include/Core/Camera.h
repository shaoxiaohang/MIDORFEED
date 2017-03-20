#pragma once
#include<Core/Matrix4.h>
#include<Core/Vector3.h>
namespace vrv
{
	class Camera
	{
	public:
		Camera();
		void setProjectionMatrixAsPerspective();
		void setProjectionMatrixAsOrtho(float l,float r,float b, float t,float n,float f);
		void setProjectionMatroxAsOrtho2D();
		Matrix4f getViewMatrix();
	protected:
		float myYaw;
		float myPitch;
		float myRoll;
		Vector3f myPosition;
	};
}
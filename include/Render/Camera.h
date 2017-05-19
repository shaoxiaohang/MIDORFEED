#pragma once
#include<Core/Matrix4.h>
#include<Core/Vector3.h>
class QKeyEvent;
namespace vrv
{
	class Camera
	{
	public:
		Camera();
		void setProjectionMatrixAsPerspective(float verticalFieldOfView, float ratioWDivedeH, float n, float f);
		void setProjectionMatrixAsPerspective(float l, float r, float b, float t, float n, float f);
		void setProjectionMatrixAsOrtho(float l, float r, float b, float t, float n, float f);
		void setProjectionMatroxAsOrtho2D(float l, float r,float b, float t);
		Matrix4f getViewMatrix();
		Matrix4f projectionMatrix();
		virtual bool handleKeyEvent(QKeyEvent* event);
	protected:
		void slot_update();
	protected:
		float myYaw;
		float myPitch;
		float myRoll;
		Vector3f myPosition;
		Matrix4f myProjectionMatrix;
		Vector3f myUp;
		Vector3f myFront;
	};
}
#pragma once
#include<Core/Matrix4.h>
#include<Core/Vector3.h>
class QKeyEvent;
class QMouseEvent;
class QWheelEvent;
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
		virtual bool handlerMouseEvent(QMouseEvent* event);
		virtual bool handlerWheelEvent(QWheelEvent* event);
		virtual Vector3f position();
	protected:
		void slot_update();
		void reset();
		void updateVectors();
	protected:
		float myYaw;
		float myPitch;
		float myRoll;
		Vector3f myPosition;
		Matrix4f myProjectionMatrix;
		Vector3f myUp;
		Vector3f myFront;
		Vector3f myRight;
		float myMoveSpeed; 
		float myRotateSpeed;
		float myZoomSpeed;
		bool myFirstMouse;
		int myLastMouseX;
		int myLastMouseY;
		float myFOV;
		float myWDivideH;
		bool myIsProjectionDirty;
		float myNearPlane;
		float myFarPlane;
	};
}
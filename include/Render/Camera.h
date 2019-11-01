#pragma once

#include<Core/Matrix4f.h>
#include<Core/Vector3f.h>
#include<Render/Node.h>

namespace vrv
{
   class WindowEvent;

	class Camera : public Node
	{
	public:

      enum CameraMode
      {
         OrbitMode,
         FreeMove
      };

		Camera();

      

		void setProjectionMatrixAsPerspective(float verticalFieldOfView, float ratioWDivedeH, float n, float f);

		void setProjectionMatrixAsPerspective(float l, float r, float b, float t, float n, float f);

		void setProjectionMatrixAsOrtho(float l, float r, float b, float t, float n, float f);

		void setProjectionMatroxAsOrtho2D(float l, float r,float b, float t);

		Matrix4f getViewMatrix();

		Matrix4f projectionMatrix();

		Vector3f position();

		void setInitialPosition(Vector3f position);

		void focousOnTarget(Vector3f position, float radius);

      void focousOnTarget(Node* node);

      void handleWindowEvent(const WindowEvent& e);

      void orbitMode(const WindowEvent& e);
      void freeMode(const WindowEvent& e);

      void setLastFrame(double);

	protected:
		void reset();
		void updateVectors();
      void handleWheelEvent(const WindowEvent& e);
	protected:
		float myYaw;
		float myPitch;
		float myRoll;
		Vector3f myPosition;
		Vector3f myInitialPosition;
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
		float myNearPlane;
		float myFarPlane;
      CameraMode myCameraMode;
      double myLastFrame;
	};
}
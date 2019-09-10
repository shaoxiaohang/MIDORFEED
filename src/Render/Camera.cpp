#include <Render/Camera.h>
#include <Render/Viewer.h>
#include <Render/NodeVisitor.h>
#include <Core/WindowEvent.h>
#include <boost/bind.hpp>
#include <iostream>
#include <Core/Utility.h>
#include <Render/Scene.h>

namespace vrv
{
   Camera::Camera()
      : myYaw(-90)
      , myPitch(0)
      , myRoll(0)
      , myUp(0, 1, 0)
      , myFront(0, 0, -1)
      , myRight(1, 0, 0)
      , myPosition(0, 0, 10)
      , myMoveSpeed(0.2f)
      , myRotateSpeed(0.02f)
      , myZoomSpeed(0.1f)
      , myFirstMouse(true)
      , myLastMouseX(0)
      , myLastMouseY(0)
      , myFOV(45)
      , myIsProjectionDirty(true)
      , myNearPlane(0.1f)
      , myFarPlane(100.0f)
      , myInitialPosition(Vector3f(0, 0, 10))
      , myWDivideH(4.0f / 3.0f)
      , myCameraMode(OrbitMode)
   {
   }

   void Camera::setProjectionMatrixAsPerspective(float verticalFieldOfView, float ratioWDivedeH, float n, float f)
   {
      myFOV = verticalFieldOfView;
      myWDivideH = ratioWDivedeH;
      myNearPlane = n;
      myFarPlane = f;
      myProjectionMatrix = Matrix4f::makeProjection(verticalFieldOfView, ratioWDivedeH, n, f);
   }

   void Camera::setProjectionMatrixAsPerspective(float l, float r, float b, float t, float n, float f)
   {
      myProjectionMatrix = Matrix4f::makeProjection(l, r, b, t, n, f);
   }

   void Camera::setProjectionMatrixAsOrtho(float l, float r, float b, float t, float n, float f)
   {
      myProjectionMatrix = Matrix4f::makeWindowingTransformation(l, b, -n, r, t, -f, -1, -1, -1, 1, 1, 1);
   }

   void Camera::setProjectionMatroxAsOrtho2D(float l, float r, float b, float t)
   {
      setProjectionMatrixAsOrtho(l, r, b, t, 0, 1);
   }

   void Camera::reset()
   {
      myYaw = -90;
      myPitch = 0;
      myRoll = 0;
      myFront = Vector3f(0, 0, -1);
      myRight = Vector3f(1, 0, 0);
      myUp = Vector3f(0, 1, 0);
      myPosition = myInitialPosition;
      myFOV = 45;
      myFirstMouse = true;
      myLastMouseX = 0;
      myLastMouseY = 0;
      myIsProjectionDirty = false;
   }

   void Camera::updateVectors()
   {
      myFront.normalize();
      Vector3f w = -myFront;
      myRight = myUp.crossProduct(w);
      myUp = w.crossProduct(myRight);
   }

   Matrix4f Camera::getViewMatrix()
   {
      Vector3f w = -myFront.normalizedVector();
      return Matrix4f::makeCanonicalToFrame(myPosition, myRight, myUp, w);
   }

   Matrix4f Camera::projectionMatrix()
   {
      if (myIsProjectionDirty)
      {
         myProjectionMatrix = Matrix4f::makeProjection(myFOV, myWDivideH, myNearPlane, myFarPlane);
         myIsProjectionDirty = false;
      }
      return myProjectionMatrix;
   }


   //bool Camera::handlerWheelEvent()
   //{
   //	//if (myFOV >= 1.0f && myFOV <= 45.0f)
   //	//{
   //	//	myFOV += event->delta()*myZoomSpeed;
   //	//}
   //	//if (myFOV <= 1.0f)
   //	//	myFOV = 1.0f;
   //	//if (myFOV >= 45.0f)
   //	//	myFOV = 45.0f;
   //	//myIsProjectionDirty = true;
   //	return true;
   //}

   Vector3f Camera::position()
   {
      return myPosition;
   }

   void Camera::setInitialPosition(Vector3f position)
   {
      myInitialPosition = position;
      reset();
   }

   void Camera::focousOnTarget(Vector3f position, float radius)
   {
      myNearPlane = 0.01f * radius;
      myFarPlane = 10 * radius;

      float distance = radius / Utility::sin(myFOV / 2.0f);

      myPosition = (Vector3f(0, 0, 1) - position).normalizedVector() * distance + position;
      setInitialPosition(myPosition);
      myIsProjectionDirty = true;
   }

   void Camera::orbitMode(const WindowEvent& e)
   {
      static float startX = 0;
      static float startY = 0;
      static ApplyRotationNodeVisitor v;
      switch (e.eventType())
      {
         case WindowEvent::MouseDown:
         {
            startX = e.mousePositionX();
            startY = e.mousePositionY();
 
         };
         break;
         case WindowEvent::MouseUp:
         {
         };
         break;
         case WindowEvent::MouseMove:
         {
            if (e.mouseButton() == WindowEvent::LeftMouseButton)
            {
               float deltaX = e.mousePositionX() - startX;
               float deltaY = e.mousePositionY() - startY;
               float speed = 0.01f;
               v.setXRotation(deltaY*speed);
               v.setYRotation(deltaX*speed);
               Scene::instance().acceptNodeVisitor(&v);
            }
         };
         break;
      };
   }

   void Camera::freeMode(const WindowEvent& e)
   {
      switch (e.eventType())
      {
      case WindowEvent::KeyBoardDown:
      {
         switch (e.keyButton())
         {
         case WindowEvent::W:
         {
            myPosition += myFront * myMoveSpeed;
         }
         break;
         case WindowEvent::S:
         {
            myPosition -= myFront * myMoveSpeed;
         }
         break;
         case WindowEvent::A:
         {
            myPosition -= myRight * myMoveSpeed;
         }
         break;
         case WindowEvent::D:
         {
            myPosition += myRight * myMoveSpeed;
         }
         break;
         case WindowEvent::Z:
         {
            reset();
         }
         break;
         default:
            break;
         }
      }
      case WindowEvent::MouseMove:
      {
         if (myFirstMouse)
         {
            myLastMouseX = e.mousePositionX();
            myLastMouseY = e.mousePositionY();
            myFirstMouse = false;
         }
         if (e.mouseButton() == WindowEvent::RightMouseButton)
         {
            float deltaX = e.mousePositionX() - myLastMouseX;
            float deltaY = e.mousePositionY() - myLastMouseY;
            myLastMouseX = e.mousePositionX();
            myLastMouseY = e.mousePositionY();
            myYaw += deltaX * myRotateSpeed;
            myPitch -= deltaY * myRotateSpeed;

            myFront.x() = Utility::cos(myPitch)*Utility::cos(myYaw);
            myFront.y() = Utility::sin(myPitch);
            myFront.z() = Utility::cos(myPitch) * Utility::sin(myYaw);
            updateVectors();
         }
         else
         {
            myLastMouseX = e.mousePositionX();
            myLastMouseY = e.mousePositionY();
         }
      }
      break;
      default:
         break;
      }
   }

   void Camera::handleWindowEvent(const WindowEvent& e)
   {
      switch (myCameraMode)
      {
      case vrv::Camera::OrbitMode:
         orbitMode(e);
         break;
      case vrv::Camera::FreeMove:
         freeMode(e);
         break;
      default:
         break;
      }
   }
}
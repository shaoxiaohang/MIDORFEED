#include <Render/Camera.h>
#include <Render/Viewer.h>
#include <boost/bind.hpp>
#include <iostream>
#include <QtGui/QKeyEvent>
#include <Core/Utility.h>
namespace vrv
{
	Camera::Camera()
		: myYaw(0)
		, myPitch(0)
		, myRoll(0)
		, myUp(0, 1, 0)
		, myFront(0, 0, -1)
		, myRight(1,0,0)
		, myPosition(0, 0, 5)
		, myMoveSpeed(0.1f)
		, myRotateSpeed(0.04f)
		, myZoomSpeed(0.1f)
		, myFirstMouse(true)
		, myLastMouseX(0)
		, myLastMouseY(0)
		, myFOV(45)
		, myIsProjectionDirty(false)
		, myNearPlane(0.1f)
		, myFarPlane(100.0f)
	{
		Viewer::signal_update.connect(
			boost::bind(&Camera::slot_update, this));
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

	void Camera::slot_update()
	{
	}

	void Camera::reset()
	{
		myYaw = 0;
		myPitch = 0;
		myRoll = 0;
		myFront = Vector3f(0, 0, -1);
		myRight = Vector3f(1, 0, 0);
		myUp = Vector3f(0, 1, 0);
		myPosition = Vector3f(0, 0, 5);
		myFOV = 45;
		myFirstMouse = true;
		myLastMouseX = 0;
		myLastMouseY = 0;
		myIsProjectionDirty = false;
	}

	void Camera::updateVectors()
	{
		Vector3f w = -myFront.normalize();
		myRight = myUp.crossProduct(w).normalize();
		myUp = w.crossProduct(myRight);
	}

	Matrix4f Camera::getViewMatrix()
	{
		Vector3f w = -myFront.normalize();
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

	bool Camera::handleKeyEvent(QKeyEvent* event)
	{
		switch (event->key())
		{
		case Qt::Key_W:
			myPosition += myFront * myMoveSpeed;
			return true;
		case Qt::Key_A:
			myPosition -= myRight*myMoveSpeed;
			return true;
		case Qt::Key_S:
			myPosition -= myFront * myMoveSpeed;
			return true;
		case Qt::Key_D:
			myPosition += myRight*myMoveSpeed;
			return true;
		case Qt::Key_Space:
			reset();
			return true;
		default:
			return false;
		}
	}

	bool Camera::handlerMouseEvent(QMouseEvent* event)
	{
		if (myFirstMouse)
		{
			myLastMouseX = event->x();
			myLastMouseY = event->y();
			myFirstMouse = false;
		}
		if (event->buttons() == Qt::RightButton)
		{
			double deltaX = event->x() - myLastMouseX;
			double deltaY = event->y() - myLastMouseY;
			myLastMouseX = event->x();
			myLastMouseY = event->y();
			myYaw += deltaX*myRotateSpeed;
			myPitch -= deltaY*myRotateSpeed;

			myFront.x = Utility::cos(myPitch)*Utility::sin(myYaw);
			myFront.y = Utility::sin(myPitch);
			myFront.z = -Utility::cos(myPitch) * Utility::cos(myYaw);
			updateVectors();
			return true;
		}
		else
		{
			myLastMouseX = event->x();
			myLastMouseY = event->y();
			return false;
		}
	}

	bool Camera::handlerWheelEvent(QWheelEvent* event)
	{
		if (myFOV >= 1.0f && myFOV <= 45.0f)
		{
			myFOV += event->delta()*myZoomSpeed;
		}
		if (myFOV <= 1.0f)
			myFOV = 1.0f;
		if (myFOV >= 45.0f)
			myFOV = 45.0f;
		myIsProjectionDirty = true;
		return true;
	}

	Vector3f Camera::position()
	{
		return myPosition;
	}
}
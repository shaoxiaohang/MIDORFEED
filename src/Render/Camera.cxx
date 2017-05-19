#include <Render/Camera.h>
#include <Render/Viewer.h>
#include <boost/bind.hpp>
#include <iostream>
#include <QtGui/QKeyEvent>
namespace vrv
{
	Camera::Camera()
		: myYaw(0)
		, myPitch(0)
		, myRoll(0)
		, myUp(0,1,0)
		, myFront(0,0,-1)
		, myPosition(0,0,3)
	{
		Viewer::signal_update.connect(
			boost::bind(&Camera::slot_update, this));
	}

	void Camera::setProjectionMatrixAsPerspective(float verticalFieldOfView, float ratioWDivedeH, float n, float f)
	{
		myProjectionMatrix = Matrix4f::makeProjection(verticalFieldOfView, ratioWDivedeH, n, f);
	}

	void Camera::setProjectionMatrixAsPerspective(float l, float r, float b, float t, float n, float f)
	{
		myProjectionMatrix = Matrix4f::makeProjection(l, r, b, t, n, f);
	}

	void Camera::setProjectionMatrixAsOrtho(float l, float r, float b, float t, float n, float f)
	{
		myProjectionMatrix = Matrix4f::makeWindowingTransformation(l, b, n, r, t, f, -1, -1, -1, 1, 1, 1);
	}

	void Camera::setProjectionMatroxAsOrtho2D(float l, float r, float b, float t)
	{
		setProjectionMatrixAsOrtho(l, r, b, t, 0, 1);
	}

	void Camera::slot_update()
	{
	}

	Matrix4f Camera::getViewMatrix()
	{
		Vector3f w = -myFront.normalize();
		Vector3f u = myUp.crossProduct(w).normalize();
		Vector3f v = w.crossProduct(u);
		return Matrix4f::makeCanonicalToFrame(myPosition, u, v, w);
	} 

	Matrix4f Camera::projectionMatrix()
	{
		return myProjectionMatrix;
	}

	bool Camera::handleKeyEvent(QKeyEvent* event)
	{
		switch (event->key())
		{
		case Qt::Key_W:
			myPosition.z -= 5;
			return true;
		case Qt::Key_A:
			myPosition.x -= 5;
			return true;
		case Qt::Key_S:
			myPosition.z += 5;
			return true;
		case Qt::Key_D:
			myPosition.x += 5;
			return true;
		default:
			return false;
		}
	}
}
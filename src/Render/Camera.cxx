#include <Render/Camera.h>

namespace vrv
{
	Camera::Camera()
		: myYaw(0)
		, myPitch(0)
		, myRoll(0)
	{}

	void Camera::setProjectionMatrixAsPerspective()
	{

	}

	void Camera::setProjectionMatrixAsOrtho(float l, float r, float b, float t, float n, float f)
	{
		myProjectionMatrix = Matrix4f::makeWindowingTransformation(l, b, n, r, t, f, -1, -1, -1, 1, 1, 1);
	}

	void Camera::setProjectionMatroxAsOrtho2D(float l, float r, float b, float t)
	{
		setProjectionMatrixAsOrtho(l, r, b, t, 0, 1);
	}

	Matrix4f Camera::getViewMatrix()
	{
		return Matrix4f();
	}

	Matrix4f Camera::projectionMatrix()
	{
		return myProjectionMatrix;
	}
}
#include <Render/ClearState.h>
#include <Render/OpenGLContext.h>


namespace vrv
{
	ClearState::ClearState()
		: myClearColor(0.05f, 0.05f, 0.05f, 1.0f)
		, myClearDepth(1.0f)
		, myClearMask(DEPTH_COLOR_STENCIL_BIT)
	{
		switch (myClearMask)
		{
		case vrv::ClearState::COLOR_BUFFER_BIT:
			myGLClearMask = GL_COLOR_BUFFER_BIT;
			break;
		case vrv::ClearState::DEPTH_BUFFER_BIT:
			myGLClearMask = GL_DEPTH_BUFFER_BIT;
			break;
		case vrv::ClearState::DEPTH_COLOR_BIT:
			myGLClearMask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
			break;
		case vrv::ClearState::DEPTH_COLOR_STENCIL_BIT:
			myGLClearMask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
			break;
		default:
			break;
		}
	}

	void ClearState::apply()
	{
		glClearColor(myClearColor.x(), myClearColor.y(), myClearColor.z(), myClearColor.w());
		glClearDepth(myClearDepth);
	}
	void ClearState::applyIfChanged(const ClearState& state)
	{
		if (myClearColor != state.clearColor())
		{
			myClearColor = state.clearColor();
			glClearColor(myClearColor.x(), myClearColor.y(), myClearColor.z(), myClearColor.w());
		}
		if (myClearDepth != state.clearDepth())
		{
			myClearDepth = state.clearDepth();
			glClearDepth(myClearDepth);
		}
	}

	Vector4f ClearState::clearColor() const
	{
		return myClearColor;
	}
	void ClearState::setClearColor(Vector4f color)
	{
		myClearColor = color;
	}

	float ClearState::clearDepth() const
	{
		return myClearDepth;
	}
	void ClearState::setClearDepth(float depth)
	{
		myClearDepth = depth;
	}

	void ClearState::clear()
	{
		glClear(myGLClearMask);
	}
}
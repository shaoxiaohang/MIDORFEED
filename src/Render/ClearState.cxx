#include <Render/ClearState.h>

#include <Render/QtContext.h>
namespace vrv
{
	ClearState::ClearState()
		: myClearColor(1.0f, 1.0f, 1.0f, 1.0f)
		, myClearDepth(1.0f)
		, myClearMask(DEPTH_COLOR_BIT)
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
		default:
			break;
		}
	}

	void ClearState::apply()
	{
		QtContext::instance().glClearColor(myClearColor.x, myClearColor.y, myClearColor.z, myClearColor.w);
		QtContext::instance().glClearDepthf(myClearDepth);
	}
	void ClearState::applyIfChanged(const ClearState& state)
	{
		if (myClearColor != state.clearColor())
		{
			myClearColor = state.clearColor();
			QtContext::instance().glClearColor(myClearColor.x, myClearColor.y, myClearColor.z, myClearColor.w);
		}
		if (myClearDepth != state.clearDepth())
		{
			myClearDepth = state.clearDepth();
			QtContext::instance().glClearDepthf(myClearDepth);
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
		QtContext::instance().glClear(myGLClearMask);
	}
}
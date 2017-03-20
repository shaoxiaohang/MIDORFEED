#include <Render/RenderState.h>
#include <GL/glew.h>
namespace vrv
{
	GLState::GLState(bool enabled)
		: myEnabled(enabled)
	{}

	void GLState::setEnabled(bool enabled)
	{
		myEnabled = enabled;
	}

	bool GLState::enabled() const
	{
		return myEnabled;
	}

	bool GLState::operator!=(const GLState& state)
	{
		return !((*this) == state);
	}

	//////////////////////////////////////////////////////////////////////////
	//DepthTest
	DepthTest::DepthTest(bool enabled)
		: GLState(enabled)
		, myDepthTestFunction(DepthTest::DEPTH_TEST_LEQUAL)
	{

	}

	bool DepthTest::operator<(const DepthTest& depth)
	{
		if (myEnabled != depth.enabled())
		{
			//sort depth disable state in front
			return !myEnabled;
		}

		if (myDepthTestFunction != depth.depthTestFunction())
		{
			return myDepthTestFunction<depth.depthTestFunction();
		}

		return true;
	}

	bool DepthTest::operator>(const DepthTest& depth)
	{
		return !((*this) < (depth));
	}
	void DepthTest::apply()
	{
		GLenum depthTest = toGLEnum();
		if (myEnabled)
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(toGLEnum());
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}
		
	}
	unsigned int DepthTest::toGLEnum()
	{
		switch (myDepthTestFunction)
		{
		case vrv::DepthTest::DEPTH_TEST_LEQUAL:
			return GL_LEQUAL;
			break;
		case vrv::DepthTest::DEPTH_TEST_GEQUAL:
			return GL_GEQUAL;
			break;
		default:
			return GL_LEQUAL;
			break;
		}
	}

	bool DepthTest::operator==(const GLState& state)
	{
		const DepthTest& depth = static_cast<const DepthTest&>(state);
		if (myEnabled != depth.enabled())
		{
			return false;
		}
		if (myDepthTestFunction != depth.myDepthTestFunction)
		{
			return false;
		}
		return true;
	}

	void DepthTest::operator=(const DepthTest& depth)
	{
		myEnabled = depth.enabled();
		myDepthTestFunction = depth.myDepthTestFunction;
	}

	DepthTest::DepthTestFunction DepthTest::depthTestFunction() const
	{
		return myDepthTestFunction;
	}

	void DepthTest::setDepthTestFunction(DepthTest::DepthTestFunction depthTest)
	{
		myDepthTestFunction = depthTest;
	}
	//DepthTest
	//////////////////////////////////////////////////////////////////////////

	RenderState::RenderState()
		: myDepthTest(true)
	{}

	void RenderState::setDepthTest(DepthTest depthTest)
	{
		myDepthTest = depthTest;
	}
	DepthTest& RenderState::depthTest()
	{
		return myDepthTest;
	}

	void RenderState::apply()
	{
		myDepthTest.apply();
	}

	void RenderState::applyIfChanged(RenderState* state)
	{
		if (myDepthTest != state->myDepthTest)
		{
			myDepthTest = state->myDepthTest;
			myDepthTest.apply();
		}
	}
}
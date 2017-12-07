#include <Render/RenderState.h>
#include <Render/QtContext.h>
namespace vrv
{
	GLState::GLState(bool enabled)
		: myEnabled(enabled)
		, myIsDirty(true)
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
		, myDepthTestFunction(DepthTest::DEPTH_FUNC_LESS)
	{
		//
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
	void DepthTest::apply(bool forceUpdate)
	{
		if (myIsDirty || forceUpdate)
		{
			update();
		}
		if (myEnabled)
		{
			QtContext::instance().glEnable(GL_DEPTH_TEST);
			QtContext::instance().glDepthFunc(myDepthTestFunction_GL);
		}
		else
		{
			QtContext::instance().glDisable(GL_DEPTH_TEST);
		}
	}

	void DepthTest::update()
	{
		switch (myDepthTestFunction)
		{
		case vrv::DepthTest::DEPTH_FUNC_LESS:
			myDepthTestFunction_GL = GL_LESS;
			break;
		case vrv::DepthTest::DEPTH_FUNC_LEQUAL:
			myDepthTestFunction_GL = GL_LEQUAL;
			break;
		case vrv::DepthTest::DEPTH_FUNC_GEQUAL:
			myDepthTestFunction_GL = GL_GEQUAL;
			break;
		default:
			myDepthTestFunction_GL = GL_LESS;
			break;
		}
		myIsDirty = false;
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
		if (myDepthTestFunction != depthTest)
		{
			myDepthTestFunction = depthTest;
			myIsDirty = true;
		}
	
	}
	//DepthTest
	//////////////////////////////////////////////////////////////////////////

	void StencilTest::setStencilMask(unsigned int mask)
	{
		if (myStencilMask != mask)
		{
			myStencilMask = mask;
			myIsDirty = true;
		}
	}

	void StencilTest::setStencilWriteMask(unsigned int mask)
	{
		if (myStencilWriteMask != mask)
		{
			myStencilWriteMask = mask;
			myIsDirty = true;
		}
	}

	StencilTest::StencilTest(bool enable)
		: GLState(enable)
		, myStencilFunction(STENCIL_FUNC_ALWAYS)
		, myStencilMask(0xFF)
		, myStencilWriteMask(0xFF)
		, myStencilRef(1)
		, myStencilOperation_sfail(STENCIL_OPER_KEEP)
		, myStencilOperation_dfail(STENCIL_OPER_KEEP)
		, myStencilOperation_sdpass(STENCIL_OPER_REPLACE)
	{}

	void StencilTest::setStencilRef(unsigned int ref)
	{
		if (myStencilRef != ref)
		{
			myStencilRef = ref;
			myIsDirty = true;
		}
	}

	void StencilTest::setStencilFucntion(StencilFunction function)
	{
		if (myStencilFunction != function)
		{
			myStencilFunction = function;
			myIsDirty = true;
		}
		
	}

	void StencilTest::setStencilOperation(StencilOperation sfail, StencilOperation dpfail, StencilOperation dppass)
	{
		bool isDirty = false;
		if (myStencilOperation_sfail != sfail)
		{
			myStencilOperation_sfail = sfail;
			myIsDirty = true;
		}
		if (myStencilOperation_dfail != dpfail)
		{
			myStencilOperation_dfail = dpfail;
			myIsDirty = true;
		}
		if (myStencilOperation_sdpass != dppass)
		{
			myStencilOperation_sdpass = dppass;
			myIsDirty = true;
		}
	}

	void StencilTest::update()
	{
		switch (myStencilFunction)
		{
		case vrv::StencilTest::STENCIL_FUNC_NEVER:
			myStencilFunction_GL = GL_NEVER;
			break;
		case vrv::StencilTest::STENCIL_FUNC_EQUAL:
			myStencilFunction_GL = GL_EQUAL;
			break;
		case vrv::StencilTest::STENCIL_FUNC_LEQUAL:
			myStencilFunction_GL = GL_LEQUAL;
			break;
		case vrv::StencilTest::STENCIL_FUNC_ALWAYS:
			myStencilFunction_GL = GL_ALWAYS;
			break;
		default:
			break;
		}

		switch (myStencilOperation_dfail)
		{
		case vrv::StencilTest::STENCIL_OPER_KEEP:
			myStencilOperation_dfail_GL = GL_KEEP;
			break;
		case vrv::StencilTest::STENCIL_OPER_REPLACE:
			myStencilOperation_dfail_GL = GL_REPLACE;
			break;
		default:
			break;
		}

		switch (myStencilOperation_sfail)
		{
		case vrv::StencilTest::STENCIL_OPER_KEEP:
			myStencilOperation_sfail_GL = GL_KEEP;
			break;
		case vrv::StencilTest::STENCIL_OPER_REPLACE:
			myStencilOperation_sfail_GL = GL_REPLACE;
			break;
		default:
			break;
		}

		switch (myStencilOperation_sdpass)
		{
		case vrv::StencilTest::STENCIL_OPER_KEEP:
			myStencilOperation_sdpass_GL = GL_KEEP;
			break;
		case vrv::StencilTest::STENCIL_OPER_REPLACE:
			myStencilOperation_sdpass_GL = GL_REPLACE;
			break;
		default:
			break;
		}

		myIsDirty = false;
	}

	void StencilTest::apply(bool forceUpdate)
	{
		if (myIsDirty || forceUpdate)
		{
			update();
		}

		if (myEnabled)
		{
			QtContext::instance().glEnable(GL_STENCIL_TEST);
			QtContext::instance().glStencilMask(myStencilWriteMask);
			QtContext::instance().glStencilFunc(myStencilFunction_GL, myStencilRef, myStencilMask);
			QtContext::instance().glStencilOp(myStencilOperation_sfail_GL, 
				myStencilOperation_dfail_GL, myStencilOperation_sdpass_GL);
		}
		else
		{
			QtContext::instance().glDisable(GL_STENCIL_TEST);
		}
	}

	bool StencilTest::operator==(const GLState& state)
	{
		const StencilTest& stencil = static_cast<const StencilTest&>(state);
		if (myStencilMask != stencil.myStencilMask)
		{
			return false;
		}
		if (myStencilFunction != stencil.myStencilFunction)
		{
			return false;
		}
		if (myStencilOperation_dfail != stencil.myStencilOperation_dfail)
		{
			return false;
		}
		if (myStencilOperation_sfail != stencil.myStencilOperation_sfail)
		{
			return false;
		}
		if (myStencilOperation_sdpass != stencil.myStencilOperation_sdpass)
		{
			return false;
		}
		return true;
	}

	void StencilTest::operator=(const StencilTest& stencil)
	{
		myStencilMask = stencil.myStencilMask;
		myStencilWriteMask = stencil.myStencilWriteMask;
		myStencilFunction = stencil.myStencilFunction;
		myStencilOperation_dfail = stencil.myStencilOperation_dfail;
		myStencilOperation_sfail = stencil.myStencilOperation_sfail;
		myStencilOperation_sdpass = stencil.myStencilOperation_sdpass;
	}

	Blending::Blending(bool enable)
		: GLState(enable)
	{
		//
	}

	void Blending::apply(bool forceUpdate)
	{
		if (myEnabled)
		{
			QtContext::instance().glEnable(GL_BLEND);
			QtContext::instance().glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else
		{
			QtContext::instance().glDisable(GL_BLEND);
		}
	}

	void Blending::update()
	{

	}

	bool Blending::operator==(const GLState& blend)
	{
		if (myEnabled == blend.enabled())
		{
			return true;
		}
		return false;
	}

	CullFace::CullFace(bool enable)
		: GLState(enable)
		, myCullFaceType(BACK)
	{
		update();
	}

	void CullFace::apply(bool forceUpdate)
	{
		if (forceUpdate)
		{
			update();
		}
		if (myEnabled)
		{
			QtContext::instance().glEnable(GL_CULL_FACE);
			QtContext::instance().glCullFace(myCullFaceType_GL);
		}
		else
		{
			QtContext::instance().glDisable(GL_CULL_FACE);
		}
	}

	void CullFace::update()
	{
		switch (myCullFaceType)
		{
		case vrv::CullFace::BACK:
			myCullFaceType_GL = GL_BACK;
			break;
		case vrv::CullFace::FRONT:
			myCullFaceType_GL = GL_FRONT;
			break;
		case vrv::CullFace::FRONT_BACK:
			myCullFaceType_GL = GL_FRONT_AND_BACK;
			break;
		default:
			break;
		}
	}

	bool CullFace::operator==(const GLState& state)
	{
		const CullFace& cullFace = static_cast<const CullFace&>(state);
		if (myEnabled == cullFace.enabled() && myCullFaceType == cullFace.myCullFaceType)
		{
			return true;
		}
		return false;
	}

	void CullFace::setCullFaceType(CullFaceType type)
	{
		if (myCullFaceType != type)
		{
			myCullFaceType = type;
			update();
		}
		
	}

	CullFace::CullFaceType CullFace::cullFaceType()
	{
		return myCullFaceType;
	}



	RenderState::RenderState()
		: myDepthTest(true)
		, myStencilTest(false)
		, myBlending(true)
		, myCullFace(false)
	{}

	void RenderState::setDepthTest(DepthTest depthTest)
	{
		myDepthTest = depthTest;
	}
	DepthTest& RenderState::depthTest()
	{
		return myDepthTest;
	}

	void RenderState::setStencilTest(StencilTest stencilTest)
	{
		myStencilTest = stencilTest;
	}
	StencilTest& RenderState::stencilTest()
	{
		return myStencilTest;
	}

	void RenderState::setCullFace(CullFace cull)
	{
		myCullFace = cull;
	}

	CullFace& RenderState::cullFace()
	{
		return myCullFace;
	}

	void RenderState::apply()
	{
		myDepthTest.apply();
		myStencilTest.apply();
		myBlending.apply();
		myCullFace.apply();
	}

	void RenderState::applyIfChanged(RenderState* state)
	{
		if (state)
		{
			//if (myDepthTest != state->myDepthTest)
			{
				myDepthTest = state->myDepthTest;
				myDepthTest.apply(true);
			}
			//if (myStencilTest != state->myStencilTest)
		{
			myStencilTest = state->myStencilTest;
			myStencilTest.apply(true);
		}
		//if (myBlending != state->myBlending)
		{
			myBlending = state->myBlending;
			myBlending.apply(true);
		}
		//if (myCullFace != state->myCullFace)
		{
			myCullFace = state->myCullFace;
			myCullFace.apply(true);
		}
		}
	}
}
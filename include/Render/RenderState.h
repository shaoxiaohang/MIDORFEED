#pragma once

namespace vrv{

	class GLState{
	public:
		GLState(bool enabled);

		virtual void apply(bool forceUpdate = false) = 0;
		virtual void update() = 0;

		virtual bool operator==(const GLState&) = 0;
		virtual bool operator!=(const GLState&);

		void setEnabled(bool enabled);
		bool enabled() const;

	protected:
		bool myEnabled;
		bool myIsDirty;
	};

	class DepthTest : public GLState{

	public:
		enum DepthTestFunction
		{
			DEPTH_FUNC_LESS,
			DEPTH_FUNC_LEQUAL,
			DEPTH_FUNC_GEQUAL
		};

		DepthTest(bool enabled);

		bool operator<(const DepthTest& depth);
		bool operator>(const DepthTest& depth);

		virtual void apply(bool forceUpdate = false);
		virtual void update();

		virtual bool operator==(const GLState&);
		virtual void operator=(const DepthTest& depth);

		DepthTestFunction depthTestFunction() const;
		void setDepthTestFunction(DepthTestFunction depthTest);

	protected:
		DepthTestFunction myDepthTestFunction;
		unsigned int myDepthTestFunction_GL;
	};

	class StencilTest : public GLState{

	public:
		enum StencilFunction
		{
			STENCIL_FUNC_NEVER,
			STENCIL_FUNC_EQUAL,
			STENCIL_FUNC_LEQUAL,
			STENCIL_FUNC_ALWAYS
		};
		enum StencilOperation
		{
			STENCIL_OPER_KEEP,
			STENCIL_OPER_REPLACE
		};
	public:
		StencilTest(bool enable);
		void setStencilMask(unsigned int);
		void setStencilWriteMask(unsigned int);
		void setStencilRef(unsigned int);
		void setStencilFucntion(StencilFunction);
		void setStencilOperation(StencilOperation sfail, StencilOperation dpfail, StencilOperation sdpass);

		virtual void apply(bool forceUpdate = false);
		virtual bool operator==(const GLState&);
		virtual void operator=(const StencilTest& depth);
		virtual void update();

	protected:
		unsigned int myStencilMask;
		unsigned int myStencilWriteMask;
		unsigned int myStencilRef;
		StencilFunction myStencilFunction;
		StencilOperation myStencilOperation_sfail;
		StencilOperation myStencilOperation_dfail;
		StencilOperation myStencilOperation_sdpass;

		unsigned int myStencilFunction_GL;

		unsigned int myStencilOperation_sfail_GL;
		unsigned int myStencilOperation_dfail_GL;
		unsigned int myStencilOperation_sdpass_GL;
	};

	class Blending : public GLState{
	public:
		Blending(bool enable);

		virtual void apply(bool forceUpdate = false);
		virtual void update();

		virtual bool operator==(const GLState&);
	};

	class CullFace : public GLState{
	public:
		enum CullFaceType
		{
			BACK,
			FRONT,
			FRONT_BACK
		};

		CullFace(bool enable);

		virtual void apply(bool forceUpdate = false);
		virtual void update();

		void setCullFaceType(CullFaceType type);
		CullFaceType cullFaceType();

		virtual bool operator==(const GLState&);

	protected:
		CullFaceType myCullFaceType;
		unsigned int myCullFaceType_GL;
	};

	class RenderState
	{
	public:
		RenderState();

		void apply();
		void applyIfChanged(RenderState* state);

		void setDepthTest(DepthTest depthTest);
		DepthTest& depthTest();

		void setStencilTest(StencilTest stencilTest);
		StencilTest& stencilTest();

		void setCullFace(CullFace cull);
		CullFace& cullFace();

	protected:
		DepthTest myDepthTest;
		StencilTest myStencilTest;
		Blending myBlending;
		CullFace myCullFace;
	};
}
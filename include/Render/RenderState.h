#pragma once

namespace vrv
{
	class GLState
	{
	public:
		GLState(bool enabled);

		virtual void apply() = 0;
		virtual unsigned int toGLEnum() = 0;

		virtual bool operator==(const GLState&) = 0;
		virtual bool operator!=(const GLState&);

		void setEnabled(bool enabled);
		bool enabled() const;

	protected:
		bool myEnabled;
	};

	class DepthTest : public GLState
	{
	public:
		enum DepthTestFunction
		{
			DEPTH_TEST_LEQUAL,
			DEPTH_TEST_GEQUAL
		};

		DepthTest(bool enabled);

		bool operator<(const DepthTest& depth);
		bool operator>(const DepthTest& depth);

		virtual void apply();
		virtual unsigned int toGLEnum();

		virtual bool operator==(const GLState&);
		virtual void operator=(const DepthTest& depth);

		DepthTestFunction depthTestFunction() const;
		void setDepthTestFunction(DepthTestFunction depthTest);

	protected:
		DepthTestFunction myDepthTestFunction;
	};

	class RenderState
	{
	public:
		RenderState();

		void apply();
		void applyIfChanged(const RenderState& state);

		void setDepthTest(DepthTest depthTest);
		DepthTest& depthTest();

	protected:
		DepthTest myDepthTest;
	};
}
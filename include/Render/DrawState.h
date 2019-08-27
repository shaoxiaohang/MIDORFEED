#pragma once

namespace vrv
{
	class RenderState;
	class Program;

	class DrawState
	{
	public:
		DrawState();
		DrawState(Program* shader);
		DrawState(RenderState* state, Program* shader);

		void setRenderState(RenderState*);
		RenderState* renderState();
		RenderState* renderState() const;

		void setProgram(Program*);
		Program* program();
		Program* program() const;

		bool operator < (DrawState& state) const;

		void bind();
		void unbind();

	protected:
		RenderState* myRenderState;
		Program* myProgram;
	};

}
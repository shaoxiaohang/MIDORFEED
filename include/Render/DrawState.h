#pragma once

namespace vrv
{
	class RenderState;
	class VertexArrayObject;
	class Program;
	class Scene;
	class RenderInfo;
	class Shader;
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

		void insertShader(Shader* shader);

	protected:
		RenderState* myRenderState;
		Program* myProgram;
	};

}
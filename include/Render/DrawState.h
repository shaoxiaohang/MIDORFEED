#pragma once

namespace vrv
{
	class RenderState;
	class VertexArrayObject;
	class Program;
	class DrawState
	{
	public:
		DrawState(RenderState* state, VertexArrayObject* vao, Program* shader);
		DrawState(VertexArrayObject* vao, Program* shader);

		void setRenderState(RenderState*);
		RenderState* renderState();
		RenderState* renderState() const;

		void setVertexArrayObject(VertexArrayObject*);
		VertexArrayObject* vertexArrayObject();
		VertexArrayObject* vertexArrayObject() const;

		void setProgram(Program*);
		Program* program();
		Program* program() const;

		bool operator < (const DrawState& state) const;

		void bind();
		void unbind();

	protected:
		RenderState* myRenderState;
		VertexArrayObject* myVertexArrayObject;
		Program* myProgram;
	};

	struct SortDrawState
	{
		bool operator()(const DrawState& left, const DrawState& right);
	};
}
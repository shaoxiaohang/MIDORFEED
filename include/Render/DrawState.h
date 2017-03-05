#pragma once

namespace vrv
{
	class RenderState;
	class VertexArray;
	class ShaderProgram;
	class DrawState
	{
	public:
		DrawState(RenderState* state, VertexArray* vao, ShaderProgram* shader);

		void setRenderState(RenderState*);
		RenderState* renderState();
		RenderState* renderState() const;

		void setVertexArray(VertexArray*);
		VertexArray* vertexArray();
		VertexArray* vertexArray() const;

		void setShaderProgram(ShaderProgram*);
		ShaderProgram* shaderProgram();
		ShaderProgram* shaderProgram() const;

	protected:
		RenderState* myRenderState;
		VertexArray* myVertexArray;
		ShaderProgram* myShaderProgram;
	};

	struct SortDrawState
	{
		bool operator()(const DrawState& left, const DrawState& right);
	};
}
#include <Render/DrawState.h>
#include <Render/RenderState.h>
#include <Render/ShaderProgram.h>
namespace vrv
{
	DrawState::DrawState(RenderState* state, VertexArray* vao, ShaderProgram* shader)
		: myRenderState(state)
		, myVertexArray(vao)
		, myShaderProgram(shader)
	{}

	void DrawState::setRenderState(RenderState* state)
	{
		myRenderState = state;
	}
	RenderState* DrawState::renderState()
	{
		return myRenderState;
	}
	RenderState* DrawState::renderState() const
	{
		return myRenderState;
	}

	void DrawState::setVertexArray(VertexArray* vao)
	{
		myVertexArray = vao;
	}
	VertexArray* DrawState::vertexArray()
	{
		return myVertexArray;
	}
	VertexArray* DrawState::vertexArray() const
	{
		return myVertexArray;
	}

	void DrawState::setShaderProgram(ShaderProgram* shader)
	{
		myShaderProgram = shader;
	}
	ShaderProgram* DrawState::shaderProgram()
	{
		return myShaderProgram;
	}
	ShaderProgram* DrawState::shaderProgram() const 
	{
		return myShaderProgram;
	}

	bool SortDrawState::operator()(const DrawState& left, const DrawState& right)
	{
		if (*(left.shaderProgram()) < *(right.shaderProgram()))
		{
			return true;
		}
		if (*(left.shaderProgram()) > *(right.shaderProgram()))
		{
			return false;
		}
		
		RenderState& leftRenderState = *(left.renderState());
		RenderState& rightRenderState = *(right.renderState());

		if (leftRenderState.depthTest() < rightRenderState.depthTest())
		{
			return true;
		}
		if (leftRenderState.depthTest() > rightRenderState.depthTest())
		{
			return false;
		}
		return true;
	}
}
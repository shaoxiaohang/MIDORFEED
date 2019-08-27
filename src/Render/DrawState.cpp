#include <Render/DrawState.h>
#include <Render/RenderState.h>
#include <Render/Program.h>
#include <Render/VertexArrayObject.h>
#include <Render/Scene.h>
namespace vrv
{
	DrawState::DrawState()
		: myRenderState(0)
		, myProgram(0)
	{
	}

	DrawState::DrawState(Program* shader)
	{
		myRenderState = new RenderState();
		myProgram = shader;
	}


	DrawState::DrawState(RenderState* state, Program* shader)
		: myRenderState(state)
		, myProgram(shader)
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

	void DrawState::setProgram(Program* shader)
	{
		myProgram = shader;
	}
	Program* DrawState::program()
	{
		return myProgram;
	}
	Program* DrawState::program() const 
	{
		return myProgram;
	}

	void DrawState::bind()
	{
		myProgram->use();
	}

	void DrawState::unbind()
	{
		myProgram->unuse();
	}

	bool DrawState::operator< (DrawState& state) const
	{
		if (*(myProgram) < *(state.program()))
		{
			return true;
		}

		RenderState& leftRenderState = *myRenderState;
		RenderState& rightRenderState = *(state.renderState());

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
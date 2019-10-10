#include <Render/StateSet.h>
#include <Render/RenderState.h>
#include <Render/Program.h>
#include <Render/VertexArrayObject.h>
#include <Render/Scene.h>
namespace vrv
{
   StateSet::StateSet()
		: myRenderState(0)
		, myProgram(0)
	{
	}

   StateSet::StateSet(Program* shader)
	{
		myRenderState = new RenderState();
		myProgram = shader;
	}


   StateSet::StateSet(RenderState* state, Program* shader)
		: myRenderState(state)
		, myProgram(shader)
	{}


	void StateSet::setRenderState(RenderState* state)
	{
		myRenderState = state;
	}

	RenderState* StateSet::renderState()
	{
		return myRenderState;
	}

	RenderState* StateSet::renderState() const
	{
		return myRenderState;
	}

	void StateSet::setProgram(Program* shader)
	{
		myProgram = shader;
	}

	Program* StateSet::program()
	{
		return myProgram;
	}

	Program* StateSet::program() const
	{
		return myProgram;
	}

	void StateSet::bind()
	{
		myProgram->use();
	}

	void StateSet::unbind()
	{
		myProgram->unuse();
	}

	bool StateSet::operator< (StateSet& state) const
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
#include <Render/DrawState.h>
#include <Render/RenderState.h>
#include <Render/Program.h>
#include <Render/VertexArrayObject.h>
namespace vrv
{
	DrawState::DrawState(RenderState* state, VertexArrayObject* vao, Program* shader)
		: myRenderState(state)
		, myVertexArrayObject(vao)
		, myProgram(shader)
	{}

	DrawState::DrawState(VertexArrayObject* vao, Program* shader)
		: myVertexArrayObject(vao)
		, myProgram(shader)
	{
		myRenderState = new RenderState();
	}

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

	void DrawState::setVertexArrayObject(VertexArrayObject* vao)
	{
		myVertexArrayObject = vao;
	}
	VertexArrayObject* DrawState::vertexArrayObject()
	{
		return myVertexArrayObject;
	}
	VertexArrayObject* DrawState::vertexArrayObject() const
	{
		return myVertexArrayObject;
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

	void DrawState::update(Scene* scene, RenderInfo& info)
	{
		if (myProgram)
		{
			myProgram->updateAutomaticUniforms(scene, info);
			myProgram->updateUniforms();
		}
	}

	void DrawState::bind()
	{
		myVertexArrayObject->bind();
		myProgram->use();
	}

	void DrawState::unbind()
	{
		myVertexArrayObject->unbind();
		myProgram->unuse();
	}

	bool DrawState::operator< (DrawState& state) const
	{
		if (*(myProgram) < *(state.program()))
		{
			return true;
		}
		if (*(myProgram) > *(state.program()))
		{
			return false;
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
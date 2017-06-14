#include <Render/Scene.h>
#include <Core/Node.h>
#include <Render/Drawable.h>
#include <Render/Program.h>
#include <Render/Context.h>
#include <Render/ClearState.h>
#include <Render/Camera.h>
#include <Render/DrawState.h>
#include <algorithm>
namespace vrv
{
	Scene* Scene::myInstance = 0;

	RenderInfo::RenderInfo(Drawable* _drawable, Vector3f _pos, Vector4f _color, bool _useColor)
		: drawable(_drawable)
		, position(_pos)
		, color(_color)
		, useColor(_useColor)
	{}

	bool RenderInfo::SortDrawable::operator()(const RenderInfo& left, const RenderInfo& right)
	{
		return *(left.drawable->drawState()) < *(right.drawable->drawState());
	}

	Scene::Scene(Context* context)
		: myContext(context)
		, myRoot(0)
	{
		myContext->setScene(this);
		myDefaultProgram = new Program("../data/shader/default.vert", "../data/shader/default.frag");
		myDefaultProgram->link();
		myClearState = new ClearState();
		myMasterCamera = new Camera();
	}

	void Scene::setSceneData(Node* root)
	{
		myRoot = root;
	}

	void Scene::cullTraverse()
	{
		myRenderlist.clear();
		std::stack<Node*> DFSStack;
		DFSStack.push(myRoot);
		DFS(DFSStack, myRoot);
	}

	void Scene::DFS(std::stack<Node*>& stack, Node* node)
	{
		addDrawableToRender(node);
		stack.pop();
		for (unsigned int i = 0; i < node->numberOfChildren(); ++i)
		{
			Node* child = node->getChild(i);
			stack.push(child);
			DFS(stack, child);
		}
	}

	void Scene::renderScene()
	{
		if (myRoot)
		{
			myContext->clear(myClearState);
			cullTraverse();
			std::sort(myRenderlist.begin(), myRenderlist.end(), RenderInfo::SortDrawable());
			RenderList::iterator itor = myRenderlist.begin();
			RenderList::iterator end = myRenderlist.end();
			for (; itor != end; ++itor)
			{
				myContext->draw(*itor);
			}
		}
	}

	Program* Scene::defaultProgram()
	{
		return myDefaultProgram;
	}

	Camera* Scene::masterCamera()
	{
		return myMasterCamera;
	}

	void Scene::addDrawableToRender(Node* node)
	{
		unsigned int numOfDrawables = node->numberOfDrawable();
		for (unsigned int i = 0; i < numOfDrawables; ++i)
		{
			myRenderlist.push_back(RenderInfo(node->getDrawable(i), node->position(), node->color(), node->useColor()));
		}
	}

	void Scene::updateLights()
	{

	}

	void Scene::addLight(Light* light)
	{
		if (light != NULL)
		{
			myLights.push_back(light);
		}
	}
}
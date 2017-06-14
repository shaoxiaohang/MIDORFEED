#pragma once
#include <vector>
#include <stack>
#include <Core/Singleton.h>
#include <Core/Vector3.h>
#include <Core/Vector4.h>
namespace vrv
{
	class Camera;
	class Node;
	class Drawable;
	class Program;
	class Context;
	class ClearState;
	class Light;

	struct RenderInfo
	{
		RenderInfo(Drawable* drawable, Vector3f pos, Vector4f color, bool useColor);
		bool useColor;
		Drawable* drawable;
		Vector3f position;
		Vector4f color;

		struct SortDrawable
		{
			bool operator()(const RenderInfo& left, const RenderInfo& right);
		};
	};



	class Scene : public Singleton<Scene>
	{
	public:
		typedef std::vector<RenderInfo> RenderList;
		typedef std::vector<Light*> LightList;
	public:
		Scene(Context* context);
		void setSceneData(Node* root);
		virtual void renderScene();
		Program* defaultProgram();
		Camera* masterCamera();
		void addLight(Light* light);
	protected:
		virtual void cullTraverse();
		virtual void DFS(std::stack<Node*>& stack, Node* node);	
		virtual void addDrawableToRender(Node* node);
		virtual void updateLights();
	protected:
		Camera* myMasterCamera;
		Node* myRoot;
		Program* myDefaultProgram;
		Context* myContext;
		ClearState* myClearState;
		RenderList myRenderlist;
		LightList myLights;
	};
}
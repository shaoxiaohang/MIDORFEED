#pragma once
#include <vector>
#include <stack>
#include <Core/Singleton.h>
#include <Core/Matrix4.h>
#include <map>
namespace vrv
{
	class Camera;
	class Node;
	class Drawable;
	class Context;
	class ClearState;
	class Light;
	class Material;
	class Program;
	class RenderState;

	struct RenderInfo
	{
		RenderInfo(Drawable* drawable, Matrix4f pos, Material* material);
		void update(Program* program);
		Drawable* drawable;
		Matrix4f modelMatrix;
		Material* material;

		struct SortDrawable
		{
			bool operator()(const RenderInfo& left, const RenderInfo& right);
		};
	};


	struct RenderQueue
	{
		typedef std::vector<RenderInfo> RenderList;

		void sortTransparentList(Camera* camera);

		RenderList myOpaqueList;
		RenderList myTransparentList;

		void clear();
	};



	class Scene : public Singleton<Scene>
	{
	public:

		typedef std::vector<Light*> LightList;
	public:
		Scene(Context* context);
		void setSceneData(Node* root);
		virtual void renderScene();
		Camera* masterCamera();
		void addLight(Light* light);
		Node* root();
		void setVisualizeDepthBuffer(bool optimize);
		void setOptimizeVisualizeDepthBuffer(bool);
		void setOutlineObjects(bool);
		void setOutlineWidth(double);
		void enableDepthTest(bool);
	protected:
		virtual void cullTraverse();
		virtual void DFS(std::stack<Node*>& stack, Node* node);	
		virtual void addDrawableToRender(Node* node);
		virtual void updateLights();
		virtual void draw();
	protected:
		Camera* myMasterCamera;
		Node* myRoot;
		Context* myContext;
		RenderState* myPhoneLightingRenderState;
		RenderState* myOutlineRenderState;
		ClearState* myClearState;
		RenderQueue myRenderQueue;
		LightList myLights;
		bool myEnableDepthTest;
		bool myVisualizeDepthBuffer;
		bool myOptimizeVisualizeDepthBuffer;
		bool myOutlineObjects;
		double myOutlineWidth;
	};
}
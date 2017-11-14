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
	class FrameBuffer;
	class MainWindow;
	class PostProcessorManager;
	class ShaderManager;

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
		RenderQueue();
		typedef std::vector<RenderInfo> RenderList;

		void sortTransparentList(Camera* camera);

		RenderList myOpaqueList;
		RenderList myTransparentList;

		void draw(Context* context, Camera* camera);
		void addToOpaqueList(const RenderInfo&);
		void addToTransparentList(const RenderInfo&);
		void clear();
		void modifyProgram(Program* program);
		void modifyRenderState(RenderState* renderState);

		Program* myModifiedProgram;
		RenderState* myModifiedRenderState;
	};



	class Scene : public Singleton<Scene>
	{
	public:

		typedef std::vector<Light*> LightList;
	public:
		Scene(MainWindow* window,Context* context);
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
	protected:
		Camera* myMasterCamera;
		Node* myRoot;
		Context* myContext;
		MainWindow* myMainWindow;
		RenderState* myPhoneLightingRenderState;
		RenderState* myOutlineRenderState;
		ClearState* myClearState;
		FrameBuffer* myDefaultFrameBuffer;
		PostProcessorManager* myPostProcessorManager;
		RenderQueue myRenderQueue;
		LightList myLights;
		ShaderManager* myShaderManager;
		bool myEnableDepthTest;
		bool myVisualizeDepthBuffer;
		bool myOptimizeVisualizeDepthBuffer;
		bool myOutlineObjects;
		double myOutlineWidth;
	};
}
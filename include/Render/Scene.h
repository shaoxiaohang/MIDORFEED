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
	class DrawState;
	class Light;
	class Material;
	class Program;
	class RenderState;
	class MainWindow;
	class PostProcessorManager;
	class Skybox;
	class Scene;
	class ShadowSystem;

	struct RenderInfo
	{
		RenderInfo(Drawable* drawable, Matrix4f modelMatrix);
		Drawable* myDrawable;
		Matrix4f myModelMatrix;
	};


	struct RenderQueue
	{
		RenderQueue();
		typedef std::vector<RenderInfo> RenderList;

		void sortTransparentList(Camera* camera);

		RenderList myOpaqueList;
		RenderList myTransparentList;

		void draw(Scene* scene,DrawState* drawState, Camera* camera);

		void addToOpaqueList(const RenderInfo&);
		void addToTransparentList(const RenderInfo&);
		void clear();
		void draw(RenderInfo& renderInfo, DrawState* drawState);
		void updateProgram(RenderInfo& renderInfo, Program*);
	};


	class Scene : public Singleton<Scene>
	{
	public:

		enum PostEffectType
		{
			Inversion,
			GrayScale,
			KernelEffect,
			Blur,
			EdgeDetection
		};

		typedef std::vector<Light*> LightList;

	public:
		Scene(MainWindow* window);
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
		void setPostEffectType(int);
		int postEffectType();
		void setSkybox(Skybox*);
		Skybox* skybox();
		void visualizeNormal(bool);
		void updateProgram(Program* program);
	protected:
		void cullTraverse();
		void DFS(std::stack<Node*>& stack, Node* node);	
		void addDrawableToRender(Node* node);
		void updateLights(Program* program);
		void initializeDrawState();
	protected:
		Camera* myMasterCamera;
		Node* myRoot;
		MainWindow* myMainWindow;
		PostProcessorManager* myPostProcessorManager;
		RenderQueue myRenderQueue;
		LightList myLights;
		bool myEnableDepthTest;
		bool myVisualizeDepthBuffer;
		bool myOptimizeVisualizeDepthBuffer;
		bool myOutlineObjects;
		double myOutlineWidth;
		int myPostEffectType;
		Skybox* mySkybox;
		bool myVisualizeNormal;
		DrawState* myPhoneLightingDrawState;
		ShadowSystem* myShadowSystem;
	};
}
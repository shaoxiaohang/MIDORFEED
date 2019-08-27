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
	class TextureQuadRender;
	class Map;
   class NodeVisitor;

	struct RenderInfo
	{
		RenderInfo(Drawable* drawable, Matrix4f modelMatrix, bool isLightPoint, bool isEllipsoid);
		Drawable* myDrawable;
		Matrix4f myModelMatrix;
		bool myIsLightPoint;
		bool myIsEllipsoid;
	};


	struct RenderQueue
	{
		RenderQueue();
		typedef std::vector<RenderInfo> RenderList;

		void sortTransparentList(Camera* camera);

		RenderList myOpaqueList;
		RenderList myTransparentList;

		void draw(Scene* scene, DrawState* drawState, Camera* camera);

		void addToOpaqueList(const RenderInfo&);
		void addToTransparentList(const RenderInfo&);
		void clear();
		void draw(RenderInfo& renderInfo, DrawState* drawState);
		void updateModelMatrix(RenderInfo& renderInfo, Program*);
		void updateMaterial(RenderInfo& renderInfo, Program*);
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
		void setMap(Map* map);
		Map* map();
      void acceptNodeVisitor(NodeVisitor* v);
	protected:
		void cullTraverse();
		void DFS(std::stack<Node*>& stack, Node* node);
		void addDrawableToRender(Node* node);
		void updateSkybox(Program* program);
		void updateLights(Program* program);
		void updateShadow(Program* program);
		void updateGlobe(Program* program);
		void initializeDrawState();
	protected:
		Camera* myMasterCamera;
		Node* myRoot;
		Node* myLightNode;
		Map* myMap;
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
		TextureQuadRender* myTextureQuadRender;
	};
}
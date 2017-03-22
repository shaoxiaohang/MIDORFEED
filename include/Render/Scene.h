//#pragma once
//#include<vector>
//#include<stack>
//#include<Core/Singleton.h>
//namespace vrv
//{
//	class Camera;
//	class Node;
//	class Drawable;
//	class Program;
//	class Context;
//	class ClearState;
//	class Scene : public Singleton<Scene>
//	{
//	public:
//		typedef std::vector<Drawable*> RenderList;
//	public:
//		Scene(Context* context);
//		void setSceneData(Node* root);
//		virtual void renderScene();
//		Program* defaultProgram();
//	protected:
//		virtual void cullTraverse();
//		virtual void DFS(std::stack<Node*>& stack, Node* node);	
//		virtual void addDrawableToRender(Node* node);
//	protected:
//		Camera* myMasterCamera;
//		Node* myRoot;
//		Program* myDefaultProgram;
//		Context* myContext;
//		ClearState* myClearState;
//		RenderList myRenderlist;
//	};
//}
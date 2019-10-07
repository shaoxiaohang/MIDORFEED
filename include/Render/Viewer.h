#pragma once
#include<string>
#include<vector>
#include<stack>
#include<boost/signals2.hpp>

namespace vrv
{
	class Node;
	class Scene;
	class Camera;
   class MainWindow;
   class WindowEvent;
   class DtGuiManager;
	class Viewer
	{	
	public:
		Viewer(int &argc, char **argv);
		void run();
		void initialize(int width, int height, const std::string& title);
		void setSceneData(Node* node);
		void onUpdateTick(double dt);
		void onRenderTick(double dt);
		Camera* masterCamera();
      Scene* scene();
      void handleWindowEvent(const WindowEvent& e);

   protected:

      void handleMessage();
      void swapBuffer();

	public:
	    static boost::signals2::signal<void()> signal_update;
	protected:
		Scene* myScene;
      MainWindow* myMainWindow;
      DtGuiManager* myGuiManager;
      bool myQuit;
      double mySecondsPerCycle;
	};
}
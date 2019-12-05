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
   class WindowManager;
   class WindowEvent;
   class GuiManager;
   class FontManager;

	class DisplayEngine
	{	
	public:

      DisplayEngine();

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
      WindowManager* myWindowManager;
      GuiManager* myGuiManager;
      FontManager* myFontManager;
      bool myQuit;
      double mySecondsPerCycle;
	};
}
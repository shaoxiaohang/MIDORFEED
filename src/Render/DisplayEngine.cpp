#include <Render/DisplayEngine.h>
#include <Render/Scene.h>
#include <Render/Camera.h>
#include <Render/Window.h>
#include <GUI/GuiManager.h>
#include <GUI/FontManager.h>
#include <GUI/WindowManager.h>
#include <windows.h>
#include <winnt.h>

namespace vrv
{
   boost::signals2::signal<void()> DisplayEngine::signal_update;

   DisplayEngine::DisplayEngine()
		: myScene(0)
      , myWindowManager(0)
      , myQuit(false)
      , mySecondsPerCycle(0)
      , myGuiManager(0)
      , myFontManager(0)
	{
      LARGE_INTEGER cycles;
      QueryPerformanceFrequency(&cycles);
      mySecondsPerCycle = 1.0 / cycles.QuadPart;
	}

   void DisplayEngine::run()
	{
      LARGE_INTEGER previous;
      QueryPerformanceCounter(&previous);
    
      double deltaT = 1.0 / 60.0;
      LARGE_INTEGER end;

      while (!myQuit)
      {
         handleMessage();
         onUpdateTick(deltaT);
         onRenderTick(deltaT);
         swapBuffer();

         QueryPerformanceCounter(&end);

         deltaT = (end.QuadPart - previous.QuadPart) * mySecondsPerCycle;

         myScene->masterCamera()->setLastFrame(deltaT);
         previous = end;
      }
      
	}

   void DisplayEngine::handleMessage()
   {
      myWindowManager->pickMessage();
   }

   void DisplayEngine::initialize(int width, int height, const std::string& title)
	{
      myWindowManager = new WindowManager(title, width, height);
      myWindowManager->initialize();

      myScene = new Scene(width, height);
      myGuiManager = new GuiManager(myScene);
      myFontManager = new FontManager();
      myFontManager->initialize();
	}

   void DisplayEngine::onUpdateTick(double dt)
	{
      myGuiManager->update(dt);
	}
    
   void DisplayEngine::onRenderTick(double dt)
	{
		if (myScene)
		{
			myScene->renderScene();       
		}
	}

   void DisplayEngine::setSceneData(Node* root)
	{
		myScene->setSceneData(root);
	}

   Camera* DisplayEngine::masterCamera()
	{
		return myScene->masterCamera();
	}

   Scene* DisplayEngine::scene()
	{
		return myScene;
	}

   void DisplayEngine::handleWindowEvent(const WindowEvent& e)
   {
      Camera* camera = masterCamera();
      if (camera)
      {
         camera->handleWindowEvent(e);
      }
   }

   void DisplayEngine::swapBuffer()
   {
      if (myWindowManager)
         myWindowManager->swapBuffers();
   }
}
#include <Render/Viewer.h>
#include <Render/Scene.h>
#include <Render/Camera.h>
#include <Render/Window.h>
#include <GUI/GuiManager.h>
#include <GUI/FontManager.h>
#include <time.h>

namespace vrv
{
	boost::signals2::signal<void()> Viewer::signal_update;

	Viewer::Viewer(int &argc, char **argv)
		: myScene(0)
      , myWindow(0)
      , myQuit(false)
      , mySecondsPerCycle(0)
      , myGuiManager(0)
      , myFontManager(0)
	{
      LARGE_INTEGER cycles;
      QueryPerformanceFrequency(&cycles);
      mySecondsPerCycle = 1.0 / cycles.QuadPart;
	}

	void Viewer::run()
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

   void Viewer::handleMessage()
   {
      myWindow->pickMessage();
   }

	void Viewer::initialize(int _width, int _height, const std::string& _title)
	{
      myWindow = new Window(this);
      myWindow->initiailze();
      myScene = new Scene(myWindow);
      myGuiManager = new GuiManager(myScene);
      myFontManager = new FontManager();
      myFontManager->initialize();
	}

	void Viewer::onUpdateTick(double dt)
	{
      myGuiManager->update(dt);
	}
    
	void Viewer::onRenderTick(double dt)
	{
		if (myScene)
		{
			myScene->renderScene();       
		}
	}

	void Viewer::setSceneData(Node* root)
	{
		myScene->setSceneData(root);
	}

	Camera* Viewer::masterCamera()
	{
		return myScene->masterCamera();
	}

	Scene* Viewer::scene()
	{
		return myScene;
	}

   void Viewer::handleWindowEvent(const WindowEvent& e)
   {
      Camera* camera = masterCamera();
      if (camera)
      {
         camera->handleWindowEvent(e);
      }
   }

   void Viewer::swapBuffer()
   {
      if (myWindow)
         myWindow->swapBuffer();
   }
}
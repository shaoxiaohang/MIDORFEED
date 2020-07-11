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
  DisplayEngine::DisplayEngine()
    : myScene(0)
    , myWindowManager(0)
    , myQuit(false)
    , mySecondsPerCycle(0)
    , master_camera_(nullptr)
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
    myWindowManager = new WindowManager(*this, title, width, height);
    myWindowManager->initialize();
    master_camera_ = new Camera();
    myScene = new Scene(master_camera_, width, height);
  }

  void DisplayEngine::onUpdateTick(double dt)
  {

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

  Scene* DisplayEngine::scene()
  {
    return myScene;
  }

  void DisplayEngine::handleWindowEvent(const WindowEvent& e)
  {
    if (master_camera_)
    {
      master_camera_->handleWindowEvent(e);
    }
  }

  void DisplayEngine::swapBuffer()
  {
    if (myWindowManager)
      myWindowManager->swapBuffers();
  }
}
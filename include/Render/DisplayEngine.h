#pragma once

#include<string>
#include<vector>
#include<stack>

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

    Scene* scene();

    void handleWindowEvent(const WindowEvent& e);

  protected:

    void handleMessage();

    void swapBuffer();

  protected:
    Scene* myScene;
    WindowManager* myWindowManager;
    bool myQuit;
    double mySecondsPerCycle;
    Camera* master_camera_;
  };
}
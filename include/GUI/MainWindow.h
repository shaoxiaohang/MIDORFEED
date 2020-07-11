#pragma once

#include <GUI/Window.h>

namespace vrv {

  class OpenGLContext;
  class DisplayEngine;

  class MainWindow : public Window
  {
  public:

    MainWindow(DisplayEngine& de, const std::string& name, int width, int height);

    void Initialize();

  protected:

    void CreateOpenGLContext();


  protected:
    OpenGLContext* opengl_context_;
  };
}
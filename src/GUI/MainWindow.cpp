#include <GUI/MainWindow.h>
#include <GUI/WindowResource.h>
#include <Render/OpenGLContext.h>
#include <GUI/WindowEventHandler.h>

namespace vrv{
  MainWindow::MainWindow(DisplayEngine& de, const std::string& name, int width, int height)
    : Window(de, GetModuleHandle(NULL), name, 0 , new WindowEventHandler(de))
    , opengl_context_(nullptr){
    setWidth(width);
    setHeight(height);
  }

  void MainWindow::Initialize() {
    CreateOpenGLContext();
  }


  void MainWindow::CreateOpenGLContext() {
    opengl_context_ = new OpenGLContext(myHandler);
    opengl_context_->initialize();
  }
}
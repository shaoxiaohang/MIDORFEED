#include <GUI/MainWindow.h>
#include <GUI/WindowResource.h>

namespace vrv
{
   MainWindow::MainWindow(const std::string& name, int width, int height)
      : Window(GetModuleHandle(NULL), name, 0)
   {
      WindowResource* mainMenu = new WindowResource(IDR_MENU_FILE, WindowResource::Resource_Menu);
      setMenu(mainMenu);
      setWidth(width);
      setHeight(height);
   }
}
#include <Render/Viewer.h>
#include <Render/Scene.h>
#include <Render/Camera.h>
#include <Render/MainWindow.h>

namespace vrv
{
	boost::signals2::signal<void()> Viewer::signal_update;

	Viewer::Viewer(int &argc, char **argv)
		: myScene(0)
      , myMainWindow(0)
	{
		
	}

	void Viewer::run()
	{
      myMainWindow->eventLoop();
	}

	void Viewer::initialize(int _width, int _height, const std::string& _title)
	{
      myMainWindow = new MainWindow(this);
      myMainWindow->initiailze();
      myScene = new Scene(myMainWindow);
	}

	void Viewer::onUpdateTick(double dt)
	{
	
	}

	void Viewer::onRenderTick()
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

}
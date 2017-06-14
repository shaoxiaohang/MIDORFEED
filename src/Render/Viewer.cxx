#include <Render/Viewer.h>
#include <CoreQt/QtMainWindow.h>
#include <Render/Scene.h>
#include <Render/Camera.h>
#include <Render/QtContext.h>
#include <QApplication>
namespace vrv
{
	boost::signals2::signal<void()> Viewer::signal_update;

	Viewer::Viewer(int &argc, char **argv)
		: myMainWindow(0)
		, myScene(0)
	{
		myQtApplication = new QApplication(argc,argv);
	}

	void Viewer::run()
	{
		myQtApplication->exec();
	}

	void Viewer::initialize(int _width, int _height, const std::string& _title)
	{
		WindowConfiguration config(_width, _height, _title);
		myMainWindow = new QtMainWindow(this,config);
		myScene = new Scene(myMainWindow->context());
	}

	void Viewer::onUpdateTick(double dt)
	{
		//signal_update();
	}

	void Viewer::onRenderTick()
	{
		myScene->renderScene();
	}

	void Viewer::setSceneData(Node* root)
	{
		myScene->setSceneData(root);
	}

	Camera* Viewer::masterCamera()
	{
		return myScene->masterCamera();
	}

	bool Viewer::handleKeyEvent(QKeyEvent* keyEvent)
	{
		return myScene->masterCamera()->handleKeyEvent(keyEvent);
	}

	bool Viewer::handleMouseEvent(QMouseEvent* mouseEvent)
	{
		return myScene->masterCamera()->handlerMouseEvent(mouseEvent);
	}

	bool Viewer::handleWheelEvent(QWheelEvent* wheelEvent)
	{
		return myScene->masterCamera()->handlerWheelEvent(wheelEvent);
	}

	Scene* Viewer::scene()
	{
		return myScene;
	}
}
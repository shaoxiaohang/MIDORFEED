#include <Render/Viewer.h>
#include <Render/QtMainWindow.h>
#include <Render/Scene.h>
#include <Render/QtContext.h>
#include <QApplication>
namespace vrv
{
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

	void Viewer::onTick()
	{
		myScene->renderScene();
	}

	void Viewer::setSceneData(Node* root)
	{
		myScene->setSceneData(root);
	}

}
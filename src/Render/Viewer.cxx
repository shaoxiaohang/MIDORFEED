//#include <Render/Viewer.h>
//#include <Render/GLFWGraphicsWindow.h>
//#include <Render/GLEWDevice.h>
//#include <Render/Scene.h>
//namespace vrv
//{
//	Viewer::Viewer()
//		: myMainWindow(0)
//		, myScene(0)
//	{
//		myDevice = new GLEWDevice();
//	}
//
//	void Viewer::run()
//	{
//		while (!myMainWindow->shouldClose())
//		{
//			onTick();
//			myMainWindow->pullEvents();
//			myMainWindow->swapBuffer();
//		}
//	}
//
//	void Viewer::initialize(int _width, int _height, const std::string& _title)
//	{
//		myDevice->initialize();
//		WindowConfiguration config(_width, _height, _title);
//		myMainWindow = GLEWDevice::instance().createGraphcisWindow(config);
//		myScene = new Scene(myMainWindow->context());
//	}
//
//	void Viewer::onTick()
//	{
//		myScene->renderScene();
//	}
//
//	void Viewer::setSceneData(Node* root)
//	{
//		myScene->setSceneData(root);
//	}
//
//}
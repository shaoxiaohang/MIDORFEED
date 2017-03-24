#pragma once
#include<string>
#include<vector>
#include<stack>


class QApplication;
namespace vrv
{
	class Node;
	class Device;
	class QtMainWindow;
	class Scene;
	class Viewer
	{
	public:
		
	public:
		Viewer(int &argc, char **argv);
		virtual void run();
		virtual void initialize(int width, int height, const std::string& title);
		virtual void setSceneData(Node* node);
		virtual void onTick();
	protected:
		Device* myDevice;
		QtMainWindow* myMainWindow;
		Scene* myScene;
		QApplication* myQtApplication;
	};
}
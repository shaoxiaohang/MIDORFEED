#pragma once
#include<string>
#include<vector>
#include<stack>
#include<boost/signals2.hpp>

class QApplication;
class QKeyEvent;
namespace vrv
{
	class Node;
	class QtMainWindow;
	class Scene;
	class Camera;
	class Viewer
	{
	public:
		
	public:
		Viewer(int &argc, char **argv);
		virtual void run();
		virtual void initialize(int width, int height, const std::string& title);
		virtual void setSceneData(Node* node);
		virtual void onUpdateTick();
		virtual void onRenderTick();
		virtual Camera* masterCamera();
		virtual bool handleKeyEvent(QKeyEvent* keyEvent);
	public:
	    static boost::signals2::signal<void()> signal_update;
	protected:
		QtMainWindow* myMainWindow;
		Scene* myScene;
		QApplication* myQtApplication;
	};
}
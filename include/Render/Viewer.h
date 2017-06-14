#pragma once
#include<string>
#include<vector>
#include<stack>
#include<boost/signals2.hpp>

class QApplication;
class QKeyEvent;
class QMouseEvent;
class QWheelEvent;
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
		virtual void onUpdateTick(double dt);
		virtual void onRenderTick();
		virtual Camera* masterCamera();
		virtual bool handleKeyEvent(QKeyEvent* keyEvent);
		virtual bool handleMouseEvent(QMouseEvent* mouseEvent);
		virtual bool handleWheelEvent(QWheelEvent* wheelEvent);
		Scene* scene();
	public:
	    static boost::signals2::signal<void()> signal_update;
	protected:
		QtMainWindow* myMainWindow;
		Scene* myScene;
		QApplication* myQtApplication;
	};
}
#include <Render/MainWindow.h>
#include <string>
#include <QOpenGLWindow>
#include <QWidget>

namespace vrv
{
	class Viewer;
	class QtContext;
	class QtApplicationWindow;

	class QtMainWindow : public QOpenGLWindow
	{
		Q_OBJECT
	public:
		QtMainWindow(QtApplicationWindow* appWindow, Viewer* viewer, WindowConfiguration configuration);
		QtApplicationWindow* appWindow();
		QtContext* context();

	public slots:
		void tick();

	protected:
		void initialize(WindowConfiguration configuration);
		virtual void createContext();
		virtual void initializeGL();
		virtual void resizeGL(int w, int h);
		virtual void paintGL();
		void paintEvent(QPaintEvent *event);
		void resizeEvent(QResizeEvent *event);
		bool event(QEvent* event);

	protected:
		virtual void updateTick(double dt);
		virtual void renderTick();

	protected:
		Viewer* myViewer;
		QtApplicationWindow* myAppWindow;
		QtContext* myContext;
		QTime* myClock;
		int myLastFrameTime;
	};

	class QtAdapter : public QWidget
	{
		Q_OBJECT
	public:
		QtAdapter(QtApplicationWindow* appWindow, Viewer* viewer, WindowConfiguration configuration);
		QtMainWindow* mainWindow();
	protected:
		QtMainWindow* myMainWindow;
	};
}
#include <Render/MainWindow.h>
#include <QOpenGLWindow>
#include <string>

class QTime;
namespace vrv
{
	class Viewer;
	class QtContext;
	class QtMainWindow : public QOpenGLWindow,public MainWindow
	{
		Q_OBJECT
	public:
		QtMainWindow(Viewer* viewer,WindowConfiguration configuration);
		virtual void initialize();
		QtContext* context();
	protected:
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
	public slots:
	void tick();
	protected:
		QtContext* myContext;
		QTime* myClock;
		int myLastFrameTime;
	};
}
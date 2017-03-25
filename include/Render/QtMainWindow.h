#include <Render/MainWindow.h>
#include <QOpenGLWindow>
namespace vrv
{
	class Viewer;
	class QtContext;
	class QtMainWindow : public MainWindow, public QOpenGLWindow
	{
	public:
		QtMainWindow(Viewer* viewer,WindowConfiguration configuration);
		virtual void initialize();
		QtContext* context();
	protected:
		virtual void createContext();
		virtual void initializeGL();
		virtual void resizeGL(int w, int h);
		virtual void paintGL();

		protected slots:
		void update();

	protected:
		QtContext* myContext;
	};
}
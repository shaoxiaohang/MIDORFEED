#pragma once

#include <QMainWindow>
#include <Render/MainWindow.h>

class QMenuBar;
class QMenu;
class QTime;

namespace vrv
{
	class QtAdapter;
	class Viewer;
	class QtContext;
	class QtMainWindow;
	class RenderSettingsWidget;
	class QtApplicationWindow : public QMainWindow, public MainWindow
	{
		Q_OBJECT
	public:
		QtApplicationWindow(Viewer* viewer,WindowConfiguration configuration);

		virtual void initialize();

		QtMainWindow* mainWindow();

		QtContext* context();

	protected:
		void setupGui();

	private slots:
		void activeDepthTestDialog();

	protected:
		Viewer* myViewer;
		QMenuBar* myMainMenuBar;
		QMenu* myRenderSettingsMenu;
		QtAdapter* myQtAdapter;;
		RenderSettingsWidget* myRenderSettingsWidget;
	};
}
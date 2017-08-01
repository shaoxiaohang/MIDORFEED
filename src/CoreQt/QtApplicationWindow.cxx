#include <CoreQt/QtApplicationWindow.h>
#include <CoreQt/QtMainWindow.h>
#include <CoreQt/RenderSettingsWidget.h>
#include <Render/Viewer.h>
#include <QMenuBar>
#include <QMenu>
#include <QTimer>
#include <QTime>
#include <QKeyEvent>
#include <iostream>
namespace vrv
{
	QtApplicationWindow::QtApplicationWindow(Viewer* viewer, WindowConfiguration configuration)
		: MainWindow(configuration)
		, myViewer(viewer)
		, myMainMenuBar(0)
		, myRenderSettingsMenu(0)
		, myRenderSettingsWidget(0)
	{
		initialize();
		setupGui();
	}

	void QtApplicationWindow::setupGui()
	{
		myMainMenuBar = new QMenuBar(this);
		myRenderSettingsMenu = myMainMenuBar->addMenu(tr("&RenderSettings"));
		QAction* depthTest = new QAction(tr("&Depth Test"), this);
		myRenderSettingsMenu->addAction(depthTest);
		connect(depthTest, &QAction::triggered, this, &QtApplicationWindow::activeDepthTestDialog);

		setCentralWidget(myQtAdapter);
	}

	void QtApplicationWindow::activeDepthTestDialog()
	{
		if (!myRenderSettingsWidget)
		{
			myRenderSettingsWidget = new RenderSettingsWidget();
		}
		myRenderSettingsWidget->show();
	}

	void QtApplicationWindow::initialize()
	{
		myQtAdapter = new QtAdapter(this, myViewer, myConfiguration);
	}

	QtContext* QtApplicationWindow::context()
	{
		return myQtAdapter->mainWindow()->context();
	}

	QtMainWindow* QtApplicationWindow::mainWindow()
	{
		return myQtAdapter->mainWindow();
	}

}
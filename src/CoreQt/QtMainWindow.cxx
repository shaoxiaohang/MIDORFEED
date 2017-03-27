#include <CoreQt/QtMainWindow.h>
#include <Render/QtContext.h>
#include <Render/Viewer.h>
#include <QTimer>
namespace vrv
{
	QtMainWindow::QtMainWindow(Viewer* viewer, WindowConfiguration configuration)
		: MainWindow(viewer,configuration)
		, QOpenGLWindow()
		, myContext(0)
	{
		initialize();
	}

	void QtMainWindow::initialize()
	{	
		setWidth(myConfiguration.width);
		setHeight(myConfiguration.height);
		setTitle(tr(myConfiguration.title.c_str()));
		QSurfaceFormat format;
		format.setVersion(3, 3);
		format.setProfile(QSurfaceFormat::CoreProfile);
		format.setRenderableType(QSurfaceFormat::OpenGL);
		format.setDepthBufferSize(myConfiguration.depthBufferSize);
		format.setRedBufferSize(myConfiguration.redBufferSize);
		format.setGreenBufferSize(myConfiguration.greenBufferSize);
		format.setBlueBufferSize(myConfiguration.blueBufferSize);
		format.setAlphaBufferSize(myConfiguration.alphaBufferSize);
		format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
		setFormat(format);

		QOpenGLWindow::show();

		createContext();

		QTimer* timer = new QTimer(this);
		connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
		timer->start(0);
	}

	void QtMainWindow::tick()
	{
		updateTick();
		renderTick();
	}

	void QtMainWindow::updateTick()
	{

	}

	void QtMainWindow::renderTick()
	{
		paintGL();
	}

	QtContext* QtMainWindow::context()
	{
		return myContext;
	}

	void QtMainWindow::createContext()
	{
		QSurfaceFormat format = QOpenGLWindow::requestedFormat();

		std::cout << "Depth Buffer Size : " << format.depthBufferSize() << std::endl;
		std::cout << "Major OpenGL Version : " << format.majorVersion() << std::endl;
		std::cout << "Minor OpenGL Version : " << format.minorVersion() << std::endl;
		myContext = new QtContext(format);
		//have to make the context current before use it
		myContext->makeCurrent(this);
		myContext->initialize();	
	}

	void QtMainWindow::paintEvent(QPaintEvent *event)
	{
		paintGL();
	}

	void QtMainWindow::resizeEvent(QResizeEvent *event)
	{
		resizeGL(this->width(), this->height());
		this->update();
	}

	void QtMainWindow::initializeGL()
	{
		resizeGL(this->width(), this->height());
	}

	void QtMainWindow::resizeGL(int w, int h)
	{
		myContext->glViewport(0, 0, w, h);
	}

	void QtMainWindow::paintGL()
	{
		if (!isExposed())
		{
			return;
		}
		myContext->makeCurrent(this);
		myViewer->onTick();
	
		myContext->glFlush();

		

		//myContext->swapBuffer(this);
	}
}


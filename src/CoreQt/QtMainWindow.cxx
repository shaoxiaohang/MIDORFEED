#include <CoreQt/QtMainWindow.h>
#include <Render/QtContext.h>
#include <Render/Viewer.h>
#include <CoreQt/QtApplicationWindow.h>
#include <QTimer>
#include <QTime>
#include <QKeyEvent>
#include <QVBoxLayout>
namespace vrv
{
	QtMainWindow::QtMainWindow(QtApplicationWindow* appWindow, Viewer* viewer, WindowConfiguration configuration)
		: QOpenGLWindow()
		, myViewer(viewer)
		, myAppWindow(appWindow)
		, myLastFrameTime(0)
		, myIsClosing(false)
	{
		initialize(configuration);
	}

	void QtMainWindow::initialize(WindowConfiguration configuration)
	{	
		setWidth(configuration.width);
		setHeight(configuration.height);
		setTitle(configuration.title.c_str());
		QSurfaceFormat format;
		format.setVersion(3, 3);
		format.setProfile(QSurfaceFormat::CoreProfile);
		format.setRenderableType(QSurfaceFormat::OpenGL);
		format.setStencilBufferSize(configuration.stentilBufferSize);
		format.setDepthBufferSize(configuration.depthBufferSize);
		format.setRedBufferSize(configuration.redBufferSize);
		format.setGreenBufferSize(configuration.greenBufferSize);
		format.setBlueBufferSize(configuration.blueBufferSize);
		format.setAlphaBufferSize(configuration.alphaBufferSize);
		format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
		format.setSamples(1);
		setFormat(format);

		QOpenGLWindow::show();

		createContext();

		myTimer = new QTimer(this);
		connect(myTimer, SIGNAL(timeout()), this, SLOT(tick()));
		myTimer->start(0);

		myClock = new QTime();
	
	}

	QtApplicationWindow* QtMainWindow::appWindow()
	{
		return myAppWindow;
	}

	void QtMainWindow::tick()
	{
		if (!myIsClosing)
		{
			if (myClock->isNull())
			{
				myClock->start();
			}
			double dt = (myClock->elapsed() - myLastFrameTime) / 1000.0f;
			myLastFrameTime = myClock->elapsed();
			updateTick(dt);
			renderTick();
		}
		else
		{
			myTimer->stop();
			delete myTimer;
		}
	}

	void QtMainWindow::updateTick(double dt)
	{
		myViewer->onUpdateTick(dt);
	}

	void QtMainWindow::renderTick()
	{
		paintGL();
	}

	bool QtMainWindow::event(QEvent* event)
	{
		switch (event->type())
		{
		case QEvent::KeyPress:
		{
			QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
			return myViewer->handleKeyEvent(keyEvent);
		}
		case QEvent::MouseMove:
		{
			QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
			return myViewer->handleMouseEvent(mouseEvent);
		}
		case QEvent::Wheel:
		{
			QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);
			return myViewer->handleWheelEvent(wheelEvent);
		}
		case QEvent::Close:
		{
			myIsClosing = true;
		}
		default:
			return QOpenGLWindow::event(event);
		}
	}

	void QtMainWindow::createContext()
	{
		QSurfaceFormat format = QOpenGLWindow::format();

		std::cout << "Depth Buffer Size : " << format.depthBufferSize() << std::endl;
		std::cout << "Stencil Buffer Size : " << format.stencilBufferSize() << std::endl;
		std::cout << "Major OpenGL Version : " << format.majorVersion() << std::endl;
		std::cout << "Minor OpenGL Version : " << format.minorVersion() << std::endl;
		myContext = new QtContext(format);
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

	QtContext* QtMainWindow::context()
	{
		return myContext;
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
		myContext->makeCurrent(this);
		myViewer->onRenderTick();

		myContext->swapBuffer(this);
	}

	QtAdapter::QtAdapter(QtApplicationWindow* appWindow, Viewer* viewer, WindowConfiguration configuration)
		: QWidget(appWindow)
	{
		myMainWindow = new QtMainWindow(appWindow, viewer, configuration);
	}

	QtMainWindow* QtAdapter::mainWindow()
	{
		return myMainWindow;
	}
}


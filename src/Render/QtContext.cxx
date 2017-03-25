#include <Render/QtContext.h>
#include <QOpenGLContext>
#include <Core/UsefulMarco.h>
#include <CoreQt/QtMainWindow.h>
namespace vrv
{
	QtContext* QtContext::myInstance = 0;
	QtContext::QtContext(const QSurfaceFormat& format)
		: QOpenGLExtraFunctions()
		, myQtOpenGLContext(0)
	{
		createQtOpenGLContext(format);
	}

	void QtContext::createQtOpenGLContext(const QSurfaceFormat& format)
	{
		myQtOpenGLContext = new QOpenGLContext();
		myQtOpenGLContext->setFormat(format);
		myQtOpenGLContext->create();
		bool valid = myQtOpenGLContext->isValid();
		if (!valid)
		{
			VRV_ERROR("Failed to create QtOpenGLContext")
		}
	}

	QOpenGLContext* QtContext::qtContext()
	{
		return myQtOpenGLContext;
	}

	void QtContext::initialize()
	{
		QOpenGLExtraFunctions::initializeOpenGLFunctions();
		forceSynGL();
	}

	void QtContext::makeCurrent(QtMainWindow* window)
	{
		myQtOpenGLContext->makeCurrent(window);
	}

	void QtContext::swapBuffer(QtMainWindow* window)
	{
		myQtOpenGLContext->swapBuffers(window);
	}
}
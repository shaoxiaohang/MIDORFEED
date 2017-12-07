#include <Render/QtContext.h>
#include <QOpenGLContext>
#include <Core/Utility.h>
#include <CoreQt/QtMainWindow.h>
namespace vrv
{
	QtContext* QtContext::myInstance = 0;
	QtContext::QtContext(const QSurfaceFormat& format)
		: QOpenGLExtraFunctions()
		, myQtOpenGLContext(0)
	{
		initializeOpenGLMaps();
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

	void QtContext::initializeOpenGLMaps()
	{
		//initialize the texture unit map)
		myTextureUnits.resize(MAXIMUM_TEXTURE_UNITS);
		for (int i = 0; i < MAXIMUM_TEXTURE_UNITS; ++i)
		{
			myTextureUnits[i].first = false;
			myTextureUnits[i].second = 0;
		}

		myTextureTargetBindings[GL_TEXTURE_2D] = 0;
	}

	QOpenGLContext* QtContext::qtContext()
	{
		return myQtOpenGLContext;
	}

	void QtContext::initialize()
	{
		QOpenGLExtraFunctions::initializeOpenGLFunctions();
	}

	void QtContext::makeCurrent(QtMainWindow* window)
	{
		myQtOpenGLContext->makeCurrent(window);
	}

	void QtContext::swapBuffer(QtMainWindow* window)
	{
		myQtOpenGLContext->swapBuffers(window);
	}

	//GL Fucntions
	//////////////////////////////////////////////////////////////////////////
	void QtContext::glBindTexture(GLenum target, GLuint texture)
	{
		if (myTextureTargetBindings[target] != texture)
		{
			myTextureTargetBindings[target] = texture;
			QOpenGLExtraFunctions::glBindTexture(target, texture);
		}
	}

	//////////////////////////////////////////////////////////////////////////
}
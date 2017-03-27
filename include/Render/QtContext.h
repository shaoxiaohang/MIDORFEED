#pragma once

#include <Core/Singleton.h>
#include <Render/Context.h>
#include <vector>
#include <map>
#include <QOpenGLExtraFunctions>

class QOpenGLContext;
class QSurfaceFormat;
namespace vrv
{
	class QtMainWindow;
	class QtContext : public Context, public QOpenGLExtraFunctions, public Singleton<QtContext>
	{
	public:
		typedef std::pair<bool, unsigned int> TextureUnit;
		//The format includes the size of the color buffers, red, green, and blue;
		//the size of the alpha buffer; the size of the depth and stencil buffers;
		//and number of samples per pixel for multisampling. 
		//In addition, the format contains surface configuration parameters such as OpenGL profile and
		//version for rendering, whether or not to enable stereo buffers, and swap behaviour.
		QtContext(const QSurfaceFormat& format);
		QOpenGLContext* qtContext();
		virtual void initialize();
		virtual void makeCurrent(QtMainWindow*);
		virtual void swapBuffer(QtMainWindow*);
	public:
		//GL Fucntions
		//////////////////////////////////////////////////////////////////////////
		void glBindTexture(GLenum target, GLuint texture);
		//////////////////////////////////////////////////////////////////////////
	protected:
		void createQtOpenGLContext(const QSurfaceFormat& format);
		void initializeOpenGLMaps();
	protected:
		QOpenGLContext* myQtOpenGLContext;
		std::vector<TextureUnit> myTextureUnits;
		std::map<unsigned int, unsigned int> myTextureTargetBindings;
	};
}
#include <Render/Image.h>
#include <Core/Utility.h>
#include <QtWidgets/QOpenGLWidget>
namespace vrv
{
	Image::Image(const std::string& file)
		: myFileName(file)
		, myWidth(0)
		, myHeight(0)
		, myQImage(0)
	{
		initialize();
	}

	unsigned int Image::width()
	{
		return myWidth;
	}

	unsigned int Image::height()
	{
		return myHeight;
	}

	unsigned int Image::internalFormatGL()
	{
		return myInternalFormatGL;
	}

	unsigned int Image::pixelFormatGL()
	{
		return myPixelFormatGL;
	}

	unsigned int Image::dataTypeGL()
	{
		return myDataTypeGL;
	}

	unsigned char* Image::dataPointer()
	{
		return myQImage->bits();
	}

	void Image::initialize()
	{
		myQImage = new QImage(myFileName.c_str());
		myWidth = myQImage->width();
		myHeight = myQImage->height();
		QImage::Format format = myQImage->format();
		switch (format)
		{
		case QImage::Format_Invalid:
			VRV_ERROR("Failed to load image" + myFileName)
			break;
		case QImage::Format_RGB32:
			myInternalFormat = IF_RGB;
			myInternalFormatGL = GL_RGB;
			myPixelFormat = PF_RGB;
			myPixelFormatGL = GL_RGB;
			myDataType = UNSIGNED_BYTE;
			myDataTypeGL = GL_UNSIGNED_BYTE;
			break;
		case QImage::Format_ARGB32:
			myInternalFormat = IF_RGBA32F;
			myInternalFormatGL = GL_RGBA32F;
			myPixelFormat = PF_RGBA;
			myPixelFormatGL = GL_RGBA;
			myDataType = FLOAT;
			myDataTypeGL = GL_FLOAT;
		case QImage::Format_RGB888:
			myInternalFormat = IF_RGB;
			myInternalFormatGL = GL_RGB;
			myPixelFormat = PF_RGB;
			myPixelFormatGL = GL_RGB;
			myDataType = UNSIGNED_BYTE;
			myDataTypeGL = GL_UNSIGNED_BYTE;
			break;
		case QImage::Format_RGBA8888:
			myInternalFormat = IF_RGBA;
			myInternalFormatGL = GL_RGBA;
			myPixelFormat = PF_RGBA;
			myPixelFormatGL = GL_RGBA;
			myDataType = UNSIGNED_BYTE;
			myDataTypeGL = GL_UNSIGNED_BYTE;
			break;
		default:
			break;
		}
	}
}
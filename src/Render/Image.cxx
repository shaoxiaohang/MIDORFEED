#include <Render/Image.h>
#include <Core/Utility.h>
#include <windows.h>
#include <FreeImage.h>
#include <Render/QtContext.h>
namespace vrv
{
	Image::Image(const std::string& file)
		: myFileName("../data/image/" + file)
		, myWidth(0)
		, myHeight(0)
		, myFIImage(0)
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
		return FreeImage_GetBits(myFIImage);
	}

	Image::ImagePixelFormat Image::pixelFormat()
	{
		return myPixelFormat;
	}

	void Image::initialize()
	{
		FREE_IMAGE_FORMAT format;
		std::string ext = Utility::getExtensionWithLowercase(myFileName);
		if (ext.compare("jpg") == 0 || ext.compare("jpeg") == 0)
		{
			format = FIF_JPEG;
		}
		else if (ext.compare("bmp") == 0)
		{
			format = FIF_BMP;
		}
		else if (ext.compare("png") == 0)
		{
			format = FIF_PNG;
		}
		else
		{
			VRV_ERROR("Image with extentsion" + ext + "is not supported!")
			return;
		}

		myFIImage = FreeImage_Load(format, myFileName.c_str());
		if (!myFIImage)
		{
			VRV_ERROR("Failed to open image" + myFileName)
		}
		myWidth  = FreeImage_GetWidth(myFIImage);
		myHeight = FreeImage_GetHeight(myFIImage);
		FREE_IMAGE_COLOR_TYPE colorType = FreeImage_GetColorType(myFIImage);
		switch (colorType)
		{
		case FIC_RGB:
			myInternalFormat = IF_RGB;
			myInternalFormatGL = GL_RGB;
			myPixelFormat = PF_RGB;
			myPixelFormatGL = GL_BGR;
			break;
		case FIC_RGBALPHA:
			myInternalFormat = IF_RGBA;
			myInternalFormatGL = GL_RGBA;
			myPixelFormat = PF_RGBA;
			myPixelFormatGL = GL_BGRA;
		default:
			break;
		}
		FREE_IMAGE_TYPE imageType = FreeImage_GetImageType(myFIImage);
		switch (imageType)
		{
		case FIT_UNKNOWN:
			break;
		case FIT_BITMAP:
			myDataType = UNSIGNED_BYTE;
			myDataTypeGL = GL_UNSIGNED_BYTE;
			break;
		case FIT_RGBF:
			myDataType = FLOAT;
			myDataTypeGL = GL_FLOAT;
			break;
		case FIT_RGBAF:
			myDataType = FLOAT;
			myDataTypeGL = GL_FLOAT;
			break;
		default:
			break;
		}
	}
}
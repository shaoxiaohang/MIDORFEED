#pragma once
#include <string>

struct FIBITMAP;
namespace vrv
{
	class Image
	{
	public:
		enum ImageInternalFormat
		{
			IF_DEPTH_COMPENENT,
			IF_DEPTH_STENCIL,
			IF_RGB,
			IF_RGBA,
			IF_RGB32F,
			IF_RGBA32F
		};
		enum ImagePixelFormat
		{
			PF_RGB,
			PF_BGR,
			PF_RGBA,
			PF_BGRA,
			PF_DEPTH_COMPONENT,
			PF_DEPTH_STENCIL
		};
		enum ImageDataType
		{
			UNSIGNED_BYTE,
			FLOAT
		};

		//! Construct a image with the given file name
		Image(const std::string& file);

		unsigned int width();

		unsigned int height();

		ImagePixelFormat pixelFormat();

		unsigned int dataTypeGL();

		unsigned char* dataPointer();

		unsigned int internalFormatGL();

		unsigned int pixelFormatGL();

	protected:
		void initialize();

	protected:
		unsigned int myWidth;
		unsigned int myHeight;
		std::string myFileName;
		ImageInternalFormat myInternalFormat;
		ImagePixelFormat myPixelFormat;
		ImageDataType myDataType;
		unsigned int myInternalFormatGL;
		unsigned int myPixelFormatGL;
		unsigned int myDataTypeGL;
		FIBITMAP* myFIImage;
	};
}
#include <Render/Texture2D.h>
#include <Render/Image.h>
#include <Render/QtContext.h>
namespace vrv
{
	Texture2D::Texture2D(int width, int height)
	{
		myTextureType = GL_TEXTURE_2D;
		myWidth = width;
		myHeight = height;

		initialize();
	}

	Texture2D::Texture2D(const std::string& fileName)
	{
		myTextureType = GL_TEXTURE_2D;
		myImage = new Image(fileName);
		initialize();
	}

	Texture2D::Texture2D(Image* image)
	{
		myTextureType = GL_TEXTURE_2D;
		myImage = image;
		initialize();
	}

	bool Texture2D::hasAlphaChannel()
	{
		if (myImage && (myImage->pixelFormat() == Image::PF_RGBA || myImage->pixelFormat() == Image::PF_BGRA) )
		{
			return true;
		}
	}

	void Texture2D::initialize()
	{
		myGenerateMipmap = false;

		QtContext::instance().glGenTextures(1, &myID);
		myTextureWrapMode = REPEAT;
		myTextureWrapModeGL = GL_REPEAT;
		myTextureFilterMode = LINEAR;
		myTextureFilterModeGL = GL_LINEAR;
		bind();
		if (myImage)
		{
			QtContext::instance().glTexImage2D(GL_TEXTURE_2D, 0, myImage->internalFormatGL(), myImage->width(),
				myImage->height(), 0, myImage->pixelFormatGL(), myImage->dataTypeGL(), myImage->dataPointer());
		}
		else
		{
			QtContext::instance().glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,myWidth,
				myHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		}

		QtContext::instance().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, myTextureWrapModeGL);
		QtContext::instance().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, myTextureWrapModeGL);
		QtContext::instance().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, myTextureFilterModeGL);
		QtContext::instance().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, myTextureFilterModeGL);
		QtContext::instance().glGenerateMipmap(GL_TEXTURE_2D);
		unbind();
	}

	void Texture2D::update()
	{
		bind();
		QtContext::instance().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, myTextureWrapModeGL);
		QtContext::instance().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, myTextureWrapModeGL);
		QtContext::instance().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, myTextureFilterModeGL);
		QtContext::instance().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, myTextureFilterModeGL);
		unbind();
	}
}
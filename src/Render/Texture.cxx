#include <Render/Texture.h>
#include <Render/Image.h>
#include <Render/QtContext.h>
namespace vrv
{
	Texture::Texture()
		: myWidth(0)
		, myHeight(0)
		, myTextureType(GL_INVALID_ENUM)
		, myImage()
	{

	}

	void Texture::bindToPoint(unsigned int bindingPoint)
	{
		myBindingPoint = bindingPoint;
		QtContext::instance().glActiveTexture(GL_TEXTURE0 + bindingPoint);
		QtContext::instance().glBindTexture(myTextureType, myID);
	}

	unsigned int Texture::textureUnit()
	{
		return myBindingPoint;
	}

	void Texture::bind()
	{
		QtContext::instance().glBindTexture(myTextureType, myID);
	}

	void Texture::initialize()
	{
		myGenerateMipmap = false;

		QtContext::instance().glGenTextures(1, &myID);
		myTextureWrapMode = REPEAT;
		myTextureWrapModeGL = GL_REPEAT;
		myTextureFilterMode = LINEAR;
		myTextureFilterModeGL = GL_LINEAR;
		bind();
		QtContext::instance().glTexImage2D(GL_TEXTURE_2D, 0, myImage->internalFormatGL(), myImage->width(),
			myImage->height(), 0, myImage->pixelFormatGL(), myImage->dataTypeGL(), myImage->dataPointer());
		QtContext::instance().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, myTextureWrapModeGL);
		QtContext::instance().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, myTextureWrapModeGL);
		QtContext::instance().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, myTextureFilterModeGL);
		QtContext::instance().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, myTextureFilterModeGL);
		QtContext::instance().glGenerateMipmap(GL_TEXTURE_2D);
		unbind();
	}

	void Texture::unbind()
	{
		QtContext::instance().glBindTexture(myTextureType, 0);
	}

	unsigned int Texture::id()
	{
		return myID;
	}

	void Texture::setTextureWrapMode(TextureWrapMode wrapMode)
	{
		if (myTextureWrapMode != wrapMode)
		{
			myTextureWrapMode = wrapMode;
			update();
		}
	}
	void Texture::setTextureFilterMode(TextureFilterMode filterMode)
	{
		if (myTextureFilterMode != filterMode)
		{
			myTextureFilterMode = filterMode;
			update();
		}
	}

	Texture::TextureWrapMode Texture::textureWrapMode()
	{
		return myTextureWrapMode;
	}

	Texture::TextureFilterMode Texture::textureFilterMode()
	{
		return myTextureFilterMode;
	}

}
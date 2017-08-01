#include <Render/Texture.h>
#include <Render/Image.h>
#include <Render/QtContext.h>
namespace vrv
{
	Texture::Texture(const std::string& fileName)
	{
		myImage = new Image(fileName);
		initialize();
	}

	Texture::Texture(Image* image)
	{
		myImage = image;
		initialize();
	}

	void Texture::bindToPoint(unsigned int bindingPoint)
	{
		myBindingPoint = bindingPoint;
		QtContext::instance().glActiveTexture(GL_TEXTURE0 + bindingPoint);
		QtContext::instance().glBindTexture(GL_TEXTURE_2D, myID);
	}

	unsigned int Texture::textureUnit()
	{
		return myBindingPoint;
	}

	void Texture::bind()
	{
		QtContext::instance().glBindTexture(GL_TEXTURE_2D, myID);
	}

	void Texture::initialize()
	{
		myGenerateMipmap = false;
		myTextureWrapMode = REPEAT;
		myTextureFilterMode = LINEAR;
		myTextureWrapModeGL = GL_REPEAT;
		myTextureFilterModeGL = GL_LINEAR;
		QtContext::instance().glGenTextures(1, &myID);
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
		QtContext::instance().glBindTexture(GL_TEXTURE_2D, 0);
	}

	unsigned int Texture::id()
	{
		return myID;
	}
}
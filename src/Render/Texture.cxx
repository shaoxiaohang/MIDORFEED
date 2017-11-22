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
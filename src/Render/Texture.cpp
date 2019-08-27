#include <Render/Texture.h>
#include <Render/Image.h>
#include <Render/OpenGLContext.h>

namespace vrv
{
	Texture::Texture()
		: myWidth(0)
		, myHeight(0)
		, myTextureType(GL_INVALID_ENUM)
		, myImage()
	{

	}

	Texture::Texture(TextureFormat format)
		: myWidth(0)
		, myHeight(0)
		, myTextureType(GL_INVALID_ENUM)
		, myImage()
		, myTextureFormat(format)
	{

	}

	void Texture::bindToPoint(unsigned int bindingPoint)
	{
		myBindingPoint = bindingPoint;
      OpenGLContext::instance().glActiveTexture(GL_TEXTURE0 + bindingPoint);
		glBindTexture(myTextureType, myID);
	}

	unsigned int Texture::textureUnit()
	{
		return myBindingPoint;
	}

	void Texture::bind()
	{
		glBindTexture(myTextureType, myID);
	}

	void Texture::unbind()
	{
		glBindTexture(myTextureType, 0);
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

			switch (myTextureWrapMode)
			{
			case vrv::Texture::REPEAT:
				myTextureWrapModeGL = GL_REPEAT;
				break;
			case vrv::Texture::CLAMP_TO_EDGE:
				myTextureWrapModeGL = GL_CLAMP_TO_EDGE;
				break;
			case vrv::Texture::CLAMP_TO_BORDER:
				myTextureWrapModeGL = GL_CLAMP_TO_BORDER;
				break;
			default:
				break;
			}


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

	void Texture::setBorderColor(Vector4f color )
	{
		myBorderColor = color;
	}
}
#include <Render/Texture2D.h>
#include <Render/Image.h>
#include <Render/OpenGLContext.h>

namespace vrv
{
	Texture2D::Texture2D(int width, int height, TextureFormat textureFormat)
		: Texture(textureFormat)
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

		glGenTextures(1, &myID);
		myTextureWrapMode = REPEAT;
		myTextureWrapModeGL = GL_REPEAT;
		myTextureFilterMode = LINEAR;
		myTextureFilterModeGL = GL_LINEAR;
		bind();
		if (myImage)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, myImage->internalFormatGL(), myImage->width(),
				myImage->height(), 0, myImage->pixelFormatGL(), myImage->dataTypeGL(), myImage->dataPointer());
		}
		else
		{
			unsigned int internalFormat;
			unsigned int format;
			unsigned int type;
			switch (myTextureFormat)
			{
			case vrv::Texture::RGB:
			{
				internalFormat = GL_RGB;
				format = GL_RGB;
				type = GL_UNSIGNED_BYTE;
			}
			break;
			case vrv::Texture::RGBA:
			{
				internalFormat = GL_RGBA;
				format = GL_RGBA;
				type = GL_UNSIGNED_BYTE;
			}
			break;
			case vrv::Texture::FLOAT16:
			{
				internalFormat = GL_RGBA16F;
				format = GL_RGBA;
				type = GL_FLOAT;
			}
			break;
			case vrv::Texture::FLOAT32:
			{
				internalFormat = GL_RGBA32F;
				format = GL_RGBA;
				type = GL_FLOAT;
			}
			break;
			default:
				break;
			}


			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat,myWidth,
				myHeight, 0, format, type, 0);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, myTextureWrapModeGL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, myTextureWrapModeGL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, myTextureFilterModeGL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, myTextureFilterModeGL);
      OpenGLContext::instance().glGenerateMipmap(GL_TEXTURE_2D);
		unbind();
	}

	void Texture2D::update()
	{
		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, myTextureWrapModeGL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, myTextureWrapModeGL);
		if (myTextureWrapMode == CLAMP_TO_BORDER)
		{
			float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, myTextureFilterModeGL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, myTextureFilterModeGL);
		unbind();
	}
}
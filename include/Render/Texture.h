#pragma once
#include <string>
#include <Core/Vector4f.h>
namespace vrv
{
	class Image;
	class Texture
	{
	public:
		enum TextureWrapMode
		{
			REPEAT,
			CLAMP_TO_EDGE,
			CLAMP_TO_BORDER
		};
		enum TextureFilterMode
		{
			NEAREST,
			LINEAR
		};
		enum TextureFormat
		{
			RGB,
			RGBA,
			FLOAT16,
			FLOAT32
		};
		Texture();
		Texture(TextureFormat format);

		void bindToPoint(unsigned int bindingPoint);
		unsigned int textureUnit();
		void bind();
		void unbind();
		unsigned int id();
		
		void setTextureWrapMode(TextureWrapMode wrapMode);
		void setTextureFilterMode(TextureFilterMode filterMode);

		TextureWrapMode textureWrapMode();
		TextureFilterMode textureFilterMode();

		void setBorderColor(Vector4f);

		virtual bool hasAlphaChannel() = 0;

	protected:
		virtual void initialize() = 0;
		virtual void update() = 0;

	protected:
		Image* myImage;
		unsigned int myBindingPoint;
		unsigned int myID;
		unsigned int myTextureType;
		TextureWrapMode myTextureWrapMode;
		TextureFilterMode myTextureFilterMode;
		unsigned int myTextureWrapModeGL;
		unsigned int myTextureFilterModeGL;
		bool myGenerateMipmap;
		unsigned int myWidth;
		unsigned int myHeight;
		Vector4f myBorderColor;
		TextureFormat myTextureFormat;
	};
}
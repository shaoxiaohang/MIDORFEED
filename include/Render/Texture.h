#pragma once
#include <string>
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
		Texture(const std::string& fileName);
		Texture(Image* image);
		void bindToPoint(unsigned int bindingPoint);
		unsigned int textureUnit();
		void bind();
		void unbind();
		unsigned int id();
		
		void setTextureWrapMode(TextureWrapMode wrapMode);
		void setTextureFilterMode(TextureFilterMode filterMode);

		TextureWrapMode textureWrapMode();
		TextureFilterMode textureFilterMode();

	protected:
		void initialize();
		void update();
	protected:
		Image* myImage;
		unsigned int myBindingPoint;
		unsigned int myID;
		TextureWrapMode myTextureWrapMode;
		TextureFilterMode myTextureFilterMode;
		unsigned int myTextureWrapModeGL;
		unsigned int myTextureFilterModeGL;
		bool myGenerateMipmap;
	};
}
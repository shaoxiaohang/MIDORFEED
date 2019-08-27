#pragma once
#include <string>
#include <Render/Texture.h>
namespace vrv
{
	class Image;
	class Texture2D : public Texture
	{
	public:
		Texture2D(int width, int height, TextureFormat textureFormat);
		Texture2D(const std::string& fileName);
		Texture2D(Image* image);
		bool hasAlphaChannel();
	protected:
		void initialize();
		void update();
	};
}
#pragma once
#include <Render/Texture.h>
#include <vector>
namespace vrv
{
	class Image;
	class Texture3D : public Texture
	{
	public:
		Texture3D(const std::vector<std::string>& names);
		bool hasAlphaChannel();

	protected:
		void initialize();
		void update();

	protected:
		std::vector<std::string> myImageNames;
		std::vector<Image*> myImages;
	};
}
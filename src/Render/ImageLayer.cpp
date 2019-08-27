#include <Render/ImageLayer.h>
#include <Render/Map.h>
#include <Render/Texture2D.h>
#include <Render/Material.h>
#include <Render/Geometry.h>
#include <Render/Ellipsoid.h>
#include <tinyxml2.h>
namespace vrv
{
	ImageLayerOption::ImageLayerOption(tinyxml2::XMLElement* option)
	{
		if (option && option->FirstChildElement("url"))
		{
			myUrl = "../data/image/" + std::string(option->FirstChildElement("url")->GetText());
		}
	}

	ImageLayer::ImageLayer(ImageLayerOption option)
		: myImageLayerOption(option)
	{
		mySource = option.myUrl;
	}

	void ImageLayer::connectToMap(Map* map)
	{
		Texture2D* texture = new Texture2D(mySource);
		map->earth()->geometry()->getOrCreateMaterial()->setTexture2D(Material::Diffuse, texture);
	}
}
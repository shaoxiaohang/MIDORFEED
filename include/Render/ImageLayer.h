#pragma once

#include <string>

namespace tinyxml2
{
	class XMLElement;
}

namespace vrv
{
	class Map;
	class ImageLayerOption
	{
	public:
		ImageLayerOption(tinyxml2::XMLElement* option);
		std::string myUrl;
	};

	class ImageLayer
	{
	public:
		ImageLayer(ImageLayerOption option);

		void connectToMap(Map* map);

	protected:
		ImageLayerOption myImageLayerOption;
		std::string mySource;
	};
}
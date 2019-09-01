#pragma once
#include <vector>
#include <Core/Vector3f.h>
namespace vrv
{
	class ImageLayer;
	class Ellipsoid;
	class Node;
	class Map
	{
	public:
		Map();

		void addImageLayer(ImageLayer* layer);

		Node* mapNode();

		Ellipsoid* earth();

		double height(Vector3f geocentric);

	protected:
		Node* myMapNode;
		Ellipsoid* myEarth;
		std::vector<ImageLayer*> myImageLayers;
	};
}
#include <Render/Map.h>
#include <Render/Texture2D.h>
#include <Render/ImageLayer.h>
#include <Render/Geometry.h>
#include <Render/Ellipsoid.h>
#include <Render/Node.h>
namespace vrv
{
	Map::Map()
	{
		myEarth = new Ellipsoid(6378137.0, 6378137.0, 6356752.314245);
		myMapNode = new Node("map");
		myMapNode->addDrawable(myEarth->geometry());
		myMapNode->setIsEllipsoid(true);
	}

	void Map::addImageLayer(ImageLayer* layer)
	{
		myImageLayers.push_back(layer);
		layer->connectToMap(this);
	}

	Node* Map::mapNode()
	{
		return myMapNode;
	}

	Ellipsoid* Map::earth()
	{
		return myEarth;
	}

	double Map::height(Vector3f geocentric)
	{
		return myEarth->height(geocentric);
	}
}
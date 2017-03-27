#pragma once
#include <Render/Drawable.h>
#include <Render/Array.h>
#include <map>
namespace vrv
{
	class Array;
	class Texture2D;
	class Geometry : public Drawable
	{
	public:
		typedef std::map<unsigned int, Texture2D*> TextureMap;
		enum VertexAttLocation
		{
			POSITION = 0,
			NORMAL   = 1,
			TEXCOORD = 2,
			COLOR    = 3
		};
		enum VertexBinding
		{
			PerVertex,
			Overall
		};
		Geometry();

		virtual void setVertex(Array* array);
		virtual void setNomral(Array* array, VertexBinding binding = PerVertex);
		virtual void setIndex(Array* array);
		virtual void setTextureCoordinate(Array* array);
		virtual void setTexture2D(Texture2D* texture, unsigned int i);
	protected:
		virtual void buildGeometry();
	protected:
		Array* myVertexArray;
		Array* myNormalArray;
		VertexBinding myNormalBinding;
		Array* myIndexArray;
		Array* myTextureCoordinateArray;
		TextureMap myTextureMap;
	};
}
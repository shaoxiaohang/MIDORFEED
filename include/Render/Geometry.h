#pragma once
#include <Render/Drawable.h>
#include <Render/Array.h>
#include <map>
namespace vrv
{
	class Array;
	class Texture2D;
	class Material;

	class Geometry : public Drawable
	{
	public:
		Geometry();
      void addVertexAttribute(unsigned int pos, Array* array);
      void addVertexIndex(Array* array);
	};
}
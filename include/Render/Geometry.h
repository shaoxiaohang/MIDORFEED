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
		enum VertexAttLocation
		{
			POSITION = 0,
			NORMAL   = 1,
			TEXCOORD = 2,
			COLOR    = 3
		};
		Geometry();

		virtual void setVertex(ArrayVec3* array);
		virtual void setVertex(ArrayVec2* array);
		virtual void setNomral(ArrayVec3* array);
		virtual void setIndex(ArrayUnsignedInt* array);
		virtual void setTextureCoordinate(ArrayVec2* array);
		virtual void setInstancedMatrices(ArrayVec3* array);

		virtual void buildGeometry();
	protected:
		ArrayVec3* myVertexArray;
		ArrayVec3* myNormalArray;
		ArrayUnsignedInt* myIndexArray;
		ArrayVec2* myTextureCoordinateArray;
		ArrayVec3* myInstancedArray;
	};
}
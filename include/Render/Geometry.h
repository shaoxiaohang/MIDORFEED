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

		void setVertex(ArrayVec3* array);
		void setVertex(ArrayVec2* array);
		void setNomral(ArrayVec3* array);
		void setTangent(ArrayVec3* array);
		void setIndex(ArrayUnsignedInt* array);
		void setTextureCoordinate(ArrayVec2* array);
		void setInstancedMatrices(ArrayVec3* array);

		void buildGeometry();
		void setBuildNormal(bool);
		void setBuildTangent(bool);
      void calculateBound();
		

	protected:
		void calculateNormal();
		void calculateTangent();

	protected:
		ArrayVec3* myVertexArray;
		ArrayVec3* myNormalArray;
		ArrayVec3* myTangentArray;
		ArrayUnsignedInt* myIndexArray;
		ArrayVec2* myTextureCoordinateArray;
		ArrayVec3* myInstancedArray;

		bool myBuildNormal;
		bool myBuildTangent;
	};
}
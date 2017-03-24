#pragma once
#include <Render/Drawable.h>
#include <Render/Array.h>
namespace vrv
{
	class Array;
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
		enum VertexBinding
		{
			PerVertex,
			Overall
		};
		Geometry();

		virtual void setVertexArray(Array* array);
		virtual void setNomralArray(Array* array, VertexBinding binding = PerVertex);
		virtual void setIndexArray(Array* array);
	protected:
		virtual void buildGeometry();
	protected:
		Array* myVertexArray;
		Array* myNormalArray;
		VertexBinding myNormalBinding;
		Array* myIndexArray;
	};
}
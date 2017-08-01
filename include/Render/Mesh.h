#pragma once

#include <Render/Geometry.h>
namespace vrv
{
	class Material;
	class Mesh : public Geometry
	{
	public:
		Mesh();

		void setMaterial(Material* material);
		Material* material();

	protected:
		Material* myMaterial;
	};
}
#include <Render/Mesh.h>

namespace vrv
{
	Mesh::Mesh()
		: myMaterial(0)
	{

	}

	void Mesh::setMaterial(Material* material)
	{
		myMaterial = material;
	}

	Material* Mesh::material()
	{
		return myMaterial;
	}
}
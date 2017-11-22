#include <Render/Mesh.h>
#include <Render/ShaderManager.h>
#include <Render/DrawState.h>
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
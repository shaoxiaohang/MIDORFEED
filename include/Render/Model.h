#pragma once

#include <Render/Geometry.h>
#include <string>
#include <vector>

struct aiNode;
struct aiScene;
struct aiMesh;

namespace vrv
{
	class Mesh;
	class Shader;
	class Model : public Geometry
	{
	public:
		Model(const std::string& name,const std::string& fileName);

		int numberOfMeshes();

		Geometry* getMesh(int i);

	protected:
		void initialize();

		void processNode(aiNode* node, const aiScene* scene);
		
		void processMesh(aiMesh* mesh, const aiScene* scene);



	protected:
		std::string myFileName;
		std::string myBaseDirectory;
		std::vector<Geometry*> myMeshes;
	};
}
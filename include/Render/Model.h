#pragma once

#include <Core/Node.h>
#include <string>
#include <vector>

class aiNode;
class aiScene;
class aiMesh;

namespace vrv
{
	class Mesh;
	class Model : public Node
	{
	public:
		Model(const std::string& name,const std::string& fileName);

	protected:
		void initialize();

		void processNode(aiNode* node, const aiScene* scene);
		
		void processMesh(aiMesh* mesh, const aiScene* scene);

	protected:
		std::string myFileName;
		std::string myBaseDirectory;
	};
}
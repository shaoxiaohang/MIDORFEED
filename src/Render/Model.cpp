#include <Render/Model.h>
#include <Render/Geometry.h>
#include <Render/Material.h>
#include <Render/Program.h>
#include <Render/DrawState.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Core/Utility.h>

namespace vrv
{
	Model::Model(const std::string& name, const std::string& fileName)
		: myFileName("../data/model/" + fileName)
	{
		initialize();
	}

	void Model::initialize()
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(myFileName, aiProcess_Triangulate| aiProcess_FlipUVs | aiProcess_GenNormals
		| aiProcess_CalcTangentSpace);
		if (!scene | scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			VRV_INFO("error loading file")
		}
		myBaseDirectory = Utility::getBaseDirectory(myFileName);
		processNode(scene->mRootNode, scene);
		VRV_INFO("finish loading file")
	}

	void Model::processNode(aiNode* node, const aiScene* scene)
	{
		//process all the meshes
		for (unsigned int i = 0; i < node->mNumMeshes; ++i)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			processMesh(mesh, scene);
		}

		for (unsigned int i = 0; i < node->mNumChildren; ++i)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	void Model::processMesh(aiMesh* mesh, const aiScene* scene)
	{
		ArrayVec3* vertices = new ArrayVec3(mesh->mNumVertices);
		ArrayVec3* normals = new ArrayVec3(mesh->mNumVertices);
		ArrayVec3* tangents = new ArrayVec3(mesh->mNumVertices);
		bool hasST = mesh->mTextureCoords[0] ? true : false;
		ArrayVec2* textureUVs= new ArrayVec2(mesh->mNumVertices);
		for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
		{
			vertices->set(i, Vector3f(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
			normals->set(i, Vector3f(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
			tangents->set(i, Vector3f(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z));
			if (hasST)
			{
				textureUVs->set(i, Vector2f(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y));
			}
		}

		ArrayUnsignedInt* indices = new ArrayUnsignedInt();
		for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; ++j)
			{
				indices->add(face.mIndices[j]);
			}
		}

		Geometry* vrvmesh = new Geometry();
		vrvmesh->setVertex(vertices);
		vrvmesh->setIndex(indices);
		vrvmesh->setNomral(normals);
		vrvmesh->setTangent(tangents);
		if (hasST)
		{
			vrvmesh->setTextureCoordinate(textureUVs);
		}
		
		Material* vrvMaterial = new Material();

		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			aiString str;
			for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); ++i)
			{
				material->GetTexture(aiTextureType_DIFFUSE, i, &str);
				vrvMaterial->setTexture2D(Material::Diffuse, myBaseDirectory + str.C_Str());
				VRV_INFO(str.C_Str())
			}

			for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_SPECULAR); ++i)
			{
				material->GetTexture(aiTextureType_SPECULAR, i, &str);
				vrvMaterial->setTexture2D(Material::Specular, myBaseDirectory + str.C_Str());
				VRV_INFO(str.C_Str())
			}

			for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_HEIGHT); ++i)
			{
				material->GetTexture(aiTextureType_HEIGHT, i, &str);
				vrvMaterial->setTexture2D(Material::Normal, myBaseDirectory + str.C_Str());
				VRV_INFO(str.C_Str())
			}
		}

		vrvmesh->setMaterial(vrvMaterial);

		myMeshes.push_back(vrvmesh);

		VRV_INFO(mesh->mName.C_Str())
	}

	int Model::numberOfMeshes()
	{
		return myMeshes.size();
	}

	Geometry* Model::getMesh(int i)
	{
		return myMeshes[i];
	}
}
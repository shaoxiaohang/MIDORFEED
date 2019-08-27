#pragma once

#include <Core/Node.h>
#include <string>
#include <Core/Vector3.h>
#include <Core/Matrix4.h>

namespace tinyxml2
{
	class XMLElement;
}

namespace vrv
{
	class Material;
	class Texture2D;
	class Scenario : public Node
	{
	public:
		Scenario(const std::string& name);

	protected:
		void parse();
		Material* parseMaterial(tinyxml2::XMLElement*);
		void parseSkybox(tinyxml2::XMLElement*);
		void parseCameraInfo(tinyxml2::XMLElement*);
		void parseObjects(tinyxml2::XMLElement*);
		void parseEarth(tinyxml2::XMLElement*);
		Texture2D* parseTexture(tinyxml2::XMLElement*);

		void createObject(const std::string& type, const std::string& name, const std::string& fileName,
			Vector3f pos, Vector3f scale, Matrix4f rotation, Material* material);
		void createInstancedObjects(const std::string& type, const std::string& name, const std::string& fileName,
			Material* material, int count, std::vector<Vector3f>& offsets, std::vector<float>& scales);
		void createLight(const std::string& type, const std::string& name, Vector3f pos, Vector3f direction,
			Vector3f ambient, Vector3f diffuse, Vector3f specular, bool castShadow);

	protected:
		std::string myFileName;
	};
}
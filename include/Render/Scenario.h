#pragma once

#include <Core/Node.h>
#include <string>
#include <Core/Vector3.h>

namespace tinyxml2
{
	class XMLElement;
}

namespace vrv
{
	class Material;
	class Scenario : public Node
	{
	public:
		Scenario(const std::string& name);

	protected:
		void parse();
		Material* parseMaterial(tinyxml2::XMLElement*);
		void createObject(const std::string& type, const std::string& name, Vector3f pos, Material* texture);
		void createLight(const std::string& type, const std::string& name, Vector3f pos, Vector3f direction,
			Vector3f ambient, Vector3f diffuse, Vector3f specular);
	protected:
		std::string myFileName;
	};
}
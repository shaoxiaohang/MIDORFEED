#pragma once

#include <Core/Node.h>
#include <string>
#include <Core/Vector3.h>
namespace vrv
{
	class Scenario : public Node
	{
	public:
		Scenario(const std::string& name);

	protected:
		void parse();
		void createObject(const std::string& type, const std::string& name, Vector3f pos, const std::string& texture);
		void createLight(const std::string& type, const std::string& name, Vector3f pos, Vector3f direction,
			Vector3f ambient, Vector3f diffuse, Vector3f specular);
	protected:
		std::string myFileName;
	};
}
#include <Render/Scenario.h>
#include <tinyxml2.h>
#include <Core/Utility.h>
#include <Render/Cube.h>
#include <Render/Material.h>
#include <Render/Texture.h>
#include <Render/Scene.h>
#include <Render/Light.h>

using namespace tinyxml2;
namespace vrv
{
	Scenario::Scenario(const std::string& name)
	{
		myFileName = "../data/scene/" + name;
		parse();
	}

	void Scenario::parse()
	{
		XMLDocument doc;
		if (doc.LoadFile(myFileName.c_str()) != XML_SUCCESS)
		{
			VRV_ERROR("failed to load xml file")
		}
		
		XMLNode* pRoot = doc.FirstChildElement("scene");
		XMLElement* objects = pRoot->FirstChildElement("objects")->FirstChildElement();
		for (; objects; objects = objects->NextSiblingElement())
		{
			std::string objectType = objects->Name();
			std::string name = objects->FirstChildElement("name")->GetText();
			Vector3f position;
			objects->FirstChildElement("position")->QueryFloatAttribute("x", &position.x);
			objects->FirstChildElement("position")->QueryFloatAttribute("y", &position.y);
			objects->FirstChildElement("position")->QueryFloatAttribute("z", &position.z);
			std::string texture = objects->FirstChildElement("texture")->GetText();
			createObject(objectType, name, position, texture);
		}
		XMLElement* lights = pRoot->FirstChildElement("lights")->FirstChildElement();
		for (; lights; lights = lights->NextSiblingElement())
		{
			std::string name = lights->Name();
			std::string type = lights->FirstChildElement("type")->GetText();
			Vector3f position;
			Vector3f direction;
			Vector3f ambient;
			Vector3f diffuse;
			Vector3f specular;

			if (lights->FirstChildElement("position"))
			{
				lights->FirstChildElement("position")->QueryFloatAttribute("x", &position.x);
				lights->FirstChildElement("position")->QueryFloatAttribute("y", &position.y);
				lights->FirstChildElement("position")->QueryFloatAttribute("z", &position.z);
			}


			if (lights->FirstChildElement("direction"))
			{
				lights->FirstChildElement("direction")->QueryFloatAttribute("x", &direction.x);
				lights->FirstChildElement("direction")->QueryFloatAttribute("y", &direction.y);
				lights->FirstChildElement("direction")->QueryFloatAttribute("z", &direction.z);
			}

			lights->FirstChildElement("ambient")->QueryFloatAttribute("r", &ambient.x);
			lights->FirstChildElement("ambient")->QueryFloatAttribute("g", &ambient.y);
			lights->FirstChildElement("ambient")->QueryFloatAttribute("b", &ambient.z);

			lights->FirstChildElement("diffuse")->QueryFloatAttribute("r", &diffuse.x);
			lights->FirstChildElement("diffuse")->QueryFloatAttribute("g", &diffuse.y);
			lights->FirstChildElement("diffuse")->QueryFloatAttribute("b", &diffuse.z);

			lights->FirstChildElement("specular")->QueryFloatAttribute("r", &specular.x);
			lights->FirstChildElement("specular")->QueryFloatAttribute("g", &specular.y);
			lights->FirstChildElement("specular")->QueryFloatAttribute("b", &specular.z);

			createLight(type, name, position, direction, ambient, diffuse, specular);
		}
	}

	void Scenario::createObject(const std::string& type, const std::string& name, Vector3f pos, const std::string& texture)
	{
		Node* child = 0;
		Material* material = 0;
		if (type == "floor")
		{
			child = new Node(name);
			Floor* floor = new Floor();
			material = new Material();
			material->setTexture(Material::Material_Diffuse, new Texture(texture));
			floor->setMaterial(material);
			child->addDrawable(floor);
			child->setPosition(pos);
			addChild(child);
		}
		else if (type == "cube")
		{
			child = new Node(name);
			Cube* cube = new Cube();
			material = new Material();
			material->setTexture(Material::Material_Diffuse, new Texture(texture));
			cube->setMaterial(material);
			child->addDrawable(cube);
			child->setPosition(pos);
			addChild(child);
		}
	}

	void Scenario::createLight(const std::string& type, const std::string& name, Vector3f pos, Vector3f direction,
		Vector3f ambient, Vector3f diffuse, Vector3f specular)
	{
		Scene* scene = Scene::instancePtr();
		Light* light = 0;
		if (type == "direction")
		{
			light = new Light(name);
			light->setType(Light::DirectionalLight);
			light->setDirection(direction);
			light->setAmbient(ambient);
			light->setDiffuse(diffuse);
			light->setSpecular(specular);
		}
		else if (type == "point")
		{
			light = new Light(name);
			light->setType(Light::PointLight);
			light->setPosition(pos);
			light->setAmbient(ambient);
			light->setDiffuse(diffuse);
			light->setSpecular(specular);
		}
		else if (type == "spot")
		{
			light = new Light(name);
			light->setType(Light::SpotLight);
			light->setPosition(pos);
			light->setAmbient(ambient);
			light->setDiffuse(diffuse);
			light->setSpecular(specular);
		}

		if (light)
		{
			scene->addLight(light);
		}
	}
}
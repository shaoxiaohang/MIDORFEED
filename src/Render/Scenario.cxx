#include <Render/Scenario.h>
#include <tinyxml2.h>
#include <Core/Utility.h>
#include <Render/Cube.h>
#include <Render/Material.h>
#include <Render/Texture2D.h>
#include <Render/Scene.h>
#include <Render/Light.h>
#include <Render/Skybox.h>
#include <Render/Model.h>
#include <vector>
#include <string>

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
		
		XMLElement* pRoot = doc.FirstChildElement("scene");

		XMLElement* skybox = pRoot->FirstChildElement("skybox");
		createSkybox(skybox);


		XMLElement* objects = pRoot->FirstChildElement("objects")->FirstChildElement();
		for (; objects; objects = objects->NextSiblingElement())
		{
			std::string objectType = objects->Name();
			std::string name = objects->FirstChildElement("name")->GetText();
			Vector3f position;
			if (objects->FirstChildElement("position"))
			{
				objects->FirstChildElement("position")->QueryFloatAttribute("x", &position.x);
				objects->FirstChildElement("position")->QueryFloatAttribute("y", &position.y);
				objects->FirstChildElement("position")->QueryFloatAttribute("z", &position.z);
			}
			std::string fileName;
			float scale = 1.0f;

			if (objects->FirstChildElement("filename"))
			{
				fileName = objects->FirstChildElement("filename")->GetText();
			}

			if (objects->FirstChildElement("scale"))
			{
				objects->FirstChildElement("scale")->QueryFloatText(&scale);
			}

			Material* material = parseMaterial(objects);

			createObject(objectType, name, fileName, position, scale, material);
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

	Material* Scenario::parseMaterial(XMLElement* object)
	{
		XMLElement* materialNode = object->FirstChildElement("material");
		if (materialNode)
		{
			Texture2D* texture = 0;
			bool discardAlpha = false;
			float discardAlphaThreshold = 0;
			XMLElement* textureNode = materialNode->FirstChildElement("texture2D");
			if (textureNode)
			{
				std::string texName = textureNode->FirstChildElement("filename")->GetText();
				texture = new Texture2D("../data/image/" + texName);
				if (textureNode->FirstChildElement("wrapmode"))
				{
					std::string wrapModeString = textureNode->FirstChildElement("wrapmode")->GetText();
					if (wrapModeString == "repeat")
					{
						texture->setTextureWrapMode(Texture::REPEAT);
					}
					else if (wrapModeString == "clamp_to_edge")
					{
						texture->setTextureWrapMode(Texture::CLAMP_TO_EDGE);
					}
				}
				if (textureNode->FirstChildElement("filtermode"))
				{
					std::string filterString = textureNode->FirstChildElement("filtermode")->GetText();
					if (filterString == "linear")
					{
						texture->setTextureFilterMode(Texture::LINEAR);
					}
					else if (filterString == "nearest")
					{
						texture->setTextureFilterMode(Texture::NEAREST);
					}
				}
			}
			XMLElement* discardAlphaNode = materialNode->FirstChildElement("discardAlpha");
			if (discardAlphaNode)
			{
				discardAlpha = true;
				discardAlphaNode->QueryFloatAttribute("threshold", &discardAlphaThreshold);
			}

			Material* material = new Material();
			if (texture)
			{
				material->setTexture2D(Material::Material_Diffuse, texture);
			}
			if (discardAlpha)
			{
				material->setDiscardAlpha(true);
				material->setDiscardAlphaThreshold(discardAlphaThreshold);
			}

			return material;

		}
		return 0;
	}

	void Scenario::createObject(const std::string& type, const std::string& name, const std::string& fileName,
		Vector3f pos, float scale, Material* material)
	{
		Node* child = 0;
		if (type == "floor")
		{
			child = new Node(name);
			Floor* floor = new Floor();
			floor->setMaterial(material);
			child->addDrawable(floor);
			child->setPosition(pos);
			child->setScale(scale);
			addChild(child);
		}
		else if (type == "cube")
		{
			child = new Node(name);
			Cube* cube = new Cube();
			cube->setMaterial(material);
			child->addDrawable(cube);
			child->setPosition(pos);
			child->setScale(scale);
			addChild(child);
		}
		else if (type == "billboard")
		{
			child = new Node(name);
			Billboard* billboard = new Billboard();
			billboard->setMaterial(material);
			child->addDrawable(billboard);
			child->setPosition(pos);
			child->setScale(scale);
			addChild(child);
		}
		else if (type == "model")
		{
			child = new	Model(name, fileName);
			child->setScale(scale);
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

	void Scenario::createSkybox(tinyxml2::XMLElement* skybox)
	{
		if (skybox)
		{
			std::vector<std::string> textures;
			std::string dataSuffix = "../data/image/";
			std::string up = skybox->FirstChildElement("up")->GetText();
			std::string down = skybox->FirstChildElement("down")->GetText();
			std::string left = skybox->FirstChildElement("left")->GetText();
			std::string right = skybox->FirstChildElement("right")->GetText();
			std::string front = skybox->FirstChildElement("front")->GetText();
			std::string back = skybox->FirstChildElement("back")->GetText();
			textures.push_back(dataSuffix + right);
			textures.push_back(dataSuffix + left);
			textures.push_back(dataSuffix + up);
			textures.push_back(dataSuffix + down);
			textures.push_back(dataSuffix + back);
			textures.push_back(dataSuffix + front);

			Skybox* skybox = new Skybox(textures);

			Scene::instance().setSkybox(skybox);
		}
	}
}
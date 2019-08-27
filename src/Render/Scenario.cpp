#include <Render/Scenario.h>
#include <tinyxml2.h>
#include <Core/Utility.h>
#include <Render/Primitives.h>
#include <Render/Material.h>
#include <Render/Texture2D.h>
#include <Render/Scene.h>
#include <Render/Light.h>
#include <Render/Skybox.h>
#include <Render/Model.h>
#include <Render/Shader.h>
#include <Render/InstancedNode.h>
#include <Render/Camera.h>
#include <Render/ImageLayer.h>
#include <Render/Map.h>
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
			return;
		}

		XMLElement* pRoot = doc.FirstChildElement("scene");

		parseEarth(pRoot);

		parseObjects(pRoot);

		parseSkybox(pRoot);

		parseCameraInfo(pRoot);

		if (pRoot->FirstChildElement("lights"))
		{
			XMLElement* lights = pRoot->FirstChildElement("lights")->FirstChildElement();

			if (lights)
			{
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
						lights->FirstChildElement("position")->QueryFloatAttribute("x", &position.x());
						lights->FirstChildElement("position")->QueryFloatAttribute("y", &position.y());
						lights->FirstChildElement("position")->QueryFloatAttribute("z", &position.z());
					}


					if (lights->FirstChildElement("direction"))
					{
						lights->FirstChildElement("direction")->QueryFloatAttribute("x", &direction.x());
						lights->FirstChildElement("direction")->QueryFloatAttribute("y", &direction.y());
						lights->FirstChildElement("direction")->QueryFloatAttribute("z", &direction.z());
					}

					lights->FirstChildElement("ambient")->QueryFloatAttribute("r", &ambient.x());
					lights->FirstChildElement("ambient")->QueryFloatAttribute("g", &ambient.y());
					lights->FirstChildElement("ambient")->QueryFloatAttribute("b", &ambient.z());

					lights->FirstChildElement("diffuse")->QueryFloatAttribute("r", &diffuse.x());
					lights->FirstChildElement("diffuse")->QueryFloatAttribute("g", &diffuse.y());
					lights->FirstChildElement("diffuse")->QueryFloatAttribute("b", &diffuse.z());

					lights->FirstChildElement("specular")->QueryFloatAttribute("r", &specular.x());
					lights->FirstChildElement("specular")->QueryFloatAttribute("g", &specular.y());
					lights->FirstChildElement("specular")->QueryFloatAttribute("b", &specular.z());

					bool cast = false;

					if (lights->FirstChildElement("cast_shadow"))
					{
						std::string castShadow = lights->FirstChildElement("cast_shadow")->GetText();
						cast = castShadow == "true";
					}

					createLight(type, name, position, direction, ambient, diffuse, specular, cast);
				}
			}
		}


	}

	Material* Scenario::parseMaterial(XMLElement* object)
	{
		XMLElement* materialNode = object->FirstChildElement("material");
		Material* material = new Material();

		if (materialNode)
		{
			bool discardAlpha = false;
			float discardAlphaThreshold = 0;
			XMLElement* textureNode = materialNode->FirstChildElement("TexturePlatte");
			if (textureNode)
			{
				XMLElement* diffuse = textureNode->FirstChildElement("diffuse");
				Texture2D* diffuseTexture = parseTexture(diffuse);
				material->setTexture2D(Material::Diffuse, diffuseTexture);

				XMLElement* normal = textureNode->FirstChildElement("normal");
				if (normal)
				{
					Texture2D* normalTexture = parseTexture(normal);
					material->setTexture2D(Material::Normal, normalTexture);
				}
			}
			XMLElement* discardAlphaNode = materialNode->FirstChildElement("discardAlpha");
			if (discardAlphaNode)
			{
				discardAlpha = true;
				discardAlphaNode->QueryFloatAttribute("threshold", &discardAlphaThreshold);
			}

			bool transParent = false;
			XMLElement* transparentNode = materialNode->FirstChildElement("transparent");
			if (transparentNode)
			{
				transparentNode->QueryBoolText(&transParent);
			}

			if (discardAlpha)
			{
				material->setDiscardAlpha(true);
				material->setDiscardAlphaThreshold(discardAlphaThreshold);
			}
			material->setTransparent(transParent);

			return material;

		}
		return 0;
	}

	void Scenario::createInstancedObjects(const std::string& type, const std::string& name, const std::string& fileName,
		Material* material, int count, std::vector<Vector3f>& offsets, std::vector<float>& scales)
	{
		InstancedNode* child = 0;
		if (type == "floor")
		{
			child = new InstancedNode(name, count, offsets, scales);
			Floor* floor = new Floor();
			floor->setMaterial(material);
			child->addDrawable(floor);
			addChild(child);
		}
		else if (type == "cube")
		{
			child = new InstancedNode(name, count, offsets, scales);
			Cube* cube = new Cube();
			cube->setMaterial(material);
			child->addDrawable(cube);
			addChild(child);
		}
		else if (type == "billboard")
		{
			child = new InstancedNode(name, count, offsets, scales);
			Billboard* billboard = new Billboard();
			billboard->setMaterial(material);
			child->addDrawable(billboard);
			addChild(child);
		}
		else if (type == "model")
		{
			Model* model = new Model(name, fileName);
			child->addDrawable(model);
			addChild(child);
		}

		if (child)
		{
			child->setUpInstanced();
		}

	}

	void Scenario::createObject(const std::string& type, const std::string& name, const std::string& fileName,
		Vector3f pos, Vector3f scale, Matrix4f rotation, Material* material)
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
			child->setRotation(rotation);
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
			child->setRotation(rotation);
			addChild(child);
		}
		else if (type == "sphere")
		{
			child = new Node(name);
			Sphere* sphere = new Sphere();
			sphere->setMaterial(material);
			child->addDrawable(sphere);
			child->setPosition(pos);
			child->setScale(scale);
			child->setIsEllipsoid(true);
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
			child->setRotation(rotation);
			addChild(child);
		}
		else if (type == "model")
		{
			child = new Node(name);
			Model* model = new Model(name, fileName);
			model->setMaterial(material);
			child->setScale(scale);
			child->setPosition(pos);
			child->addDrawable(model);
			child->setRotation(rotation);
			addChild(child);
		}
	}

	void Scenario::createLight(const std::string& type, const std::string& name, Vector3f pos, Vector3f direction,
		Vector3f ambient, Vector3f diffuse, Vector3f specular, bool castShadow)
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
			light->setCastShadow(castShadow);
		}
		else if (type == "point")
		{
			light = new Light(name);
			light->setType(Light::PointLight);
			light->setPosition(pos);
			light->setAmbient(ambient);
			light->setDiffuse(diffuse);
			light->setSpecular(specular);
			light->setCastShadow(castShadow);
		}
		else if (type == "spot")
		{
			light = new Light(name);
			light->setType(Light::SpotLight);
			light->setPosition(pos);
			light->setAmbient(ambient);
			light->setDiffuse(diffuse);
			light->setSpecular(specular);
			light->setCastShadow(castShadow);
		}

		if (light)
		{
			scene->addLight(light);
		}
	}

	void Scenario::parseSkybox(tinyxml2::XMLElement* scene)
	{
		XMLElement* skybox = scene->FirstChildElement("skybox");
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

	Texture2D* Scenario::parseTexture(tinyxml2::XMLElement* node)
	{
		std::string texName = node->FirstChildElement("filename")->GetText();
		Texture2D* texture = new Texture2D("../data/image/" + texName);

		if (node->FirstChildElement("wrapmode"))
		{
			std::string wrapModeString = node->FirstChildElement("wrapmode")->GetText();
			if (wrapModeString == "repeat")
			{
				texture->setTextureWrapMode(Texture::REPEAT);
			}
			else if (wrapModeString == "clamp_to_edge")
			{
				texture->setTextureWrapMode(Texture::CLAMP_TO_EDGE);
			}
		}
		if (node->FirstChildElement("filtermode"))
		{
			std::string filterString = node->FirstChildElement("filtermode")->GetText();
			if (filterString == "linear")
			{
				texture->setTextureFilterMode(Texture::LINEAR);
			}
			else if (filterString == "nearest")
			{
				texture->setTextureFilterMode(Texture::NEAREST);
			}
		}

		return texture;
	}

	void Scenario::parseCameraInfo(tinyxml2::XMLElement* scene)
	{
		XMLElement* camera = scene->FirstChildElement("camera");
		if (camera)
		{
			Vector3f position;
			if (camera->FirstChildElement("position"))
			{
				camera->FirstChildElement("position")->QueryFloatAttribute("x", &position.x());
				camera->FirstChildElement("position")->QueryFloatAttribute("y", &position.y());
				camera->FirstChildElement("position")->QueryFloatAttribute("z", &position.z());
			}

			Scene::instance().masterCamera()->setInitialPosition(position);
		}
	}

	void Scenario::parseEarth(tinyxml2::XMLElement* root)
	{
		if (root)
		{
			XMLElement* earth = root->FirstChildElement("earth");
			if (earth)
			{
				Map* map = new Map();
				XMLElement* imageLayerNode = earth->FirstChildElement("image_layer");
				for (; imageLayerNode; imageLayerNode = imageLayerNode->NextSiblingElement())
				{
					ImageLayerOption imageLayerOption(imageLayerNode);
					ImageLayer* imageLayer = new ImageLayer(imageLayerOption);
					map->addImageLayer(imageLayer);
				}

				Scene::instance().setMap(map);
				addChild(map->mapNode());
			}			
		}
	}

	void Scenario::parseObjects(tinyxml2::XMLElement* root)
	{
		XMLElement* objects = root->FirstChildElement("objects");
		if (objects)
		{
			XMLElement* object = objects->FirstChildElement();
			for (; object; object = object->NextSiblingElement())
			{
				std::string objectType = object->Name();
				std::string name = object->FirstChildElement("name")->GetText();
				std::string fileName;
				if (object->FirstChildElement("filename"))
				{
					fileName = object->FirstChildElement("filename")->GetText();
				}
				Material* material = parseMaterial(object);

				if (object->FirstChildElement("instanced"))
				{
					XMLElement* instanced = object->FirstChildElement("instanced");
					int count;
					XMLElement* countElement = instanced->FirstChildElement("count");
					countElement->QueryIntText(&count);
					std::vector<Vector3f> offsets;
					std::vector<float> scales;
					XMLElement* offsetxml = countElement->NextSiblingElement("offset");
					XMLElement* scalexml = countElement->NextSiblingElement("scale");
					for (int i = 0; i < count; ++i)
					{
						Vector3f offset;
						float scale;
						offsetxml->QueryFloatAttribute("x", &offset.x());
						offsetxml->QueryFloatAttribute("y", &offset.y());
						offsetxml->QueryFloatAttribute("z", &offset.z());
						scalexml->QueryFloatText(&scale);
						offsets.push_back(offset);
						scales.push_back(scale);
						offsetxml = offsetxml->NextSiblingElement("offset");
						scalexml = scalexml->NextSiblingElement("scale");
					}

					createInstancedObjects(objectType, name, fileName, material, count, offsets, scales);

				}
				else
				{
					Vector3f position;
					if (object->FirstChildElement("position"))
					{
						object->FirstChildElement("position")->QueryFloatAttribute("x", &position.x());
						object->FirstChildElement("position")->QueryFloatAttribute("y", &position.y());
						object->FirstChildElement("position")->QueryFloatAttribute("z", &position.z());
					}

					Vector3f scale(1.0f);

					Matrix4f rotation;

					if (object->FirstChildElement("scale"))
					{
						object->FirstChildElement("scale")->QueryFloatAttribute("x", &scale.x());
						object->FirstChildElement("scale")->QueryFloatAttribute("y", &scale.y());
						object->FirstChildElement("scale")->QueryFloatAttribute("z", &scale.z());
					}

					if (object->FirstChildElement("rotation"))
					{
						std::string axis = object->FirstChildElement("rotation")->Attribute("axis");
						float degree = 0;
						object->FirstChildElement("rotation")->QueryFloatAttribute("degree", &degree);

						if (axis == "x")
						{
							rotation = Matrix4f::makeRotateX(degree);
						}
						else if (axis == "y")
						{
							rotation = Matrix4f::makeRotateY(degree);
						}
						else if (axis == "z")
						{
							rotation = Matrix4f::makeRotateZ(degree);
						}
					}

					createObject(objectType, name, fileName, position, scale, rotation, material);
				}
			}
		}

	}
}
#include <Render/Material.h>
#include <Render/Texture.h>

namespace vrv
{
	Material::Material()
		: myDiffuse(1,1,1)
		, myAmbient(0.2,0.2,0.2)
		, mySpecular(1,1,1)
		, myShininess(128)
	{}

	void Material::setAmbient(Vector3f ambient)
	{
		myAmbient = ambient;
	}

	void Material::setDiffuse(Vector3f diffuse)
	{
		myDiffuse = diffuse;
	}

	void Material::setSpecular(Vector3f specular)
	{
		mySpecular = specular;
	}

	void Material::setShininess(float shininess)
	{
		myShininess = shininess;
	}

	Vector3f Material::ambient()
	{
		return myAmbient;
	}

	Vector3f Material::diffuse()
	{
		return myDiffuse;
	}

	Vector3f Material::specular()
	{
		return mySpecular;
	}

	float Material::shininess()
	{
		return myShininess;
	}

	Texture* Material::getTexture(TextureType type)
	{
		if (myTextureMap.find(type) != myTextureMap.end())
		{
			return myTextureMap[type];
		}
		else
		{
			return NULL;
		}
	}


	void Material::setTexture(TextureType textureType, Texture* texture)
	{
		myTextureMap[textureType] = texture;
	}

	void Material::setTexture(TextureType textureType, const std::string& texture)
	{
		myTextureMap[textureType] = new Texture(texture);
	}

	bool Material::hasDiffuse()
	{
		return myTextureMap.find(Material_Diffuse) != myTextureMap.end();
	}

	bool Material::hasSpecular()
	{
		return myTextureMap.find(Material_Specular) != myTextureMap.end();
	}
}
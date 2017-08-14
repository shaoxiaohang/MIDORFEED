#include <Render/Material.h>
#include <Render/Texture.h>

namespace vrv
{
	Material::Material()
		: myDiffuse(1,1,1,1)
		, myAmbient(0.2,0.2,0.2,1)
		, mySpecular(1,1,1,1)
		, myShininess(128)
		, myDiscardAlpha(false)
		, myDiscardAlphaThreshold(0)
	{}

	void Material::setAmbient(Vector4f ambient)
	{
		myAmbient = ambient;
	}

	void Material::setDiffuse(Vector4f diffuse)
	{
		myDiffuse = diffuse;
	}

	void Material::setSpecular(Vector4f specular)
	{
		mySpecular = specular;
	}

	void Material::setShininess(float shininess)
	{
		myShininess = shininess;
	}

	void Material::setDiscardAlpha(bool value)
	{
		myDiscardAlpha = value;
	}

	void Material::setDiscardAlphaThreshold(float value)
	{
		myDiscardAlphaThreshold = value;
	}

	Vector4f Material::ambient()
	{
		return myAmbient;
	}

	Vector4f Material::diffuse()
	{
		return myDiffuse;
	}

	Vector4f Material::specular()
	{
		return mySpecular;
	}

	float Material::shininess()
	{
		return myShininess;
	}

	bool Material::discardAlpha()
	{
		return myDiscardAlpha;
	}

	float Material::discardAlphaThreshold()
	{
		return myDiscardAlphaThreshold;
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

	bool Material::isTransParent()
	{
		if (myDiffuse.w != 1)
		{
			return true;
		}
		else
		{
			if (hasDiffuse() && myTextureMap[Material_Diffuse]->hasAlphaChannel())
			{
				return true;
			}
			return false;
		}
	
	}
}
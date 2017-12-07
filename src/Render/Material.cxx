#include <Render/Material.h>
#include <Render/Texture2D.h>
#include <Render/Program.h>
#include <Render/QtContext.h>
namespace vrv
{
	Material::Material()
		: myDiffuse(1,1,1,1)
		, myAmbient(0.2,0.2,0.2,1)
		, mySpecular(1,1,1,1)
		, myShininess(128)
		, myDiscardAlpha(false)
		, myDiscardAlphaThreshold(0)
		, myIsTransparent(false)
		, myShader(0)
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

	void Material::setTransparent(bool value)
	{
		myIsTransparent = value;
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


	Texture2D* Material::getTexture2D(TextureType type)
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


	void Material::setTexture2D(TextureType textureType, Texture2D* texture)
	{
		myTextureMap[textureType] = texture;
	}

	void Material::setTexture2D(TextureType textureType, const std::string& texture)
	{
		myTextureMap[textureType] = new Texture2D(texture);
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
		bool possibleTrans = false;

		if (myDiffuse.w != 1)
		{
			possibleTrans = true;
		}
		else
		{
			if (hasDiffuse() && myTextureMap[Material_Diffuse]->hasAlphaChannel())
			{
				possibleTrans = true;
			}
		}
	
		return myIsTransparent && possibleTrans;
	}

	void Material::setPostProcessShader(Shader* shader)
	{
		myShader = shader;
	}

	Shader* Material::postProcessShader()
	{
		return myShader;
	}

	void Material::updateProgram(Program* program)
	{
		program->set("vrv_isTransparent", myIsTransparent);
		Texture2D* diffuse = getTexture2D(Material_Diffuse);
		if (diffuse)
		{
			QtContext::instance().glActiveTexture(GL_TEXTURE0 + Material::Material_Diffuse);
			QtContext::instance().glBindTexture(GL_TEXTURE_2D, diffuse->id());
		}
		Texture2D* specular = getTexture2D(Material_Specular);
		if (specular)
		{
			QtContext::instance().glActiveTexture(GL_TEXTURE0 + Material::Material_Specular);
			QtContext::instance().glBindTexture(GL_TEXTURE_2D, specular->id());
		}
		program->set("vrv_discardAlpha", myDiscardAlpha);
		program->set("vrv_discardAlphaThreshold", myDiscardAlphaThreshold);
		program->set("vrv_material.hasDiffuse", hasDiffuse());
		program->set("vrv_material.hasSpecular", hasSpecular());
		program->set("vrv_material.diffuse_tex", Material_Diffuse);
		program->set("vrv_material.specular_tex", Material_Specular);
		program->set("vrv_material.ambient", myAmbient);
		program->set("vrv_material.diffuse", myDiffuse);
		program->set("vrv_material.specular", mySpecular);
		program->set("vrv_material.shininess", myShininess);
	}
}
#pragma once
#include <Core/Vector3.h>
#include <map>
namespace vrv
{
	class Texture;
	class Material
	{
	public:
		enum TextureType
		{
			Material_Diffuse,
			Material_Specular
		};
		typedef std::map<unsigned int, Texture*> TextureMap;
	public:
		Material();

		void setAmbient(Vector3f);
		void setDiffuse(Vector3f);
		void setSpecular(Vector3f);
		void setShininess(float);
		void setDiscardAlpha(bool);
		void setDiscardAlphaThreshold(float);

		Vector3f ambient();
		Vector3f diffuse();
		Vector3f specular();
		float shininess();

		Texture* getTexture(TextureType type);

		virtual void setTexture(TextureType textureType, const std::string& texture);

		virtual void setTexture(TextureType textureType, Texture* texture);

		bool hasDiffuse();

		bool hasSpecular();

	protected:
		Vector3f myAmbient;
		Vector3f myDiffuse;
		Vector3f mySpecular;
		float myShininess;
		TextureMap myTextureMap;
		bool myDiscardAlpha;
		float myDiscardAlphaThreshold;
	};
}
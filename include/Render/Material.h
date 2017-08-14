#pragma once
#include <Core/Vector4.h>
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

		void setAmbient(Vector4f);
		void setDiffuse(Vector4f);
		void setSpecular(Vector4f);
		void setShininess(float);
		void setDiscardAlpha(bool);
		void setDiscardAlphaThreshold(float);

		Vector4f ambient();
		Vector4f diffuse();
		Vector4f specular();
		float shininess();
		bool discardAlpha();
		float discardAlphaThreshold();

		Texture* getTexture(TextureType type);
		virtual void setTexture(TextureType textureType, const std::string& texture);
		virtual void setTexture(TextureType textureType, Texture* texture);
		bool hasDiffuse();
		bool hasSpecular();
		bool isTransParent();

	protected:
		Vector4f		myAmbient;
		Vector4f		myDiffuse;
		Vector4f		mySpecular;
		float			myShininess;
		TextureMap  myTextureMap;
		bool			myDiscardAlpha;
		float		   myDiscardAlphaThreshold;
	};
}
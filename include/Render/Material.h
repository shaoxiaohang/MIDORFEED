#pragma once
#include <Core/Vector4f.h>
#include <map>
namespace vrv
{
	class Texture2D;
	class Shader;
	class Program;
	class Material
	{
	public:
		enum TextureType
		{
			Diffuse,
			Specular,
			Normal
		};
		typedef std::map<unsigned int, Texture2D*> TextureMap;
	public:
		Material();

		void setAmbient(Vector4f);
		void setDiffuse(Vector4f);
		void setSpecular(Vector4f);
		void setShininess(float);
		void setDiscardAlpha(bool);
		void setDiscardAlphaThreshold(float);
		void setTransparent(bool);

		Vector4f ambient();
		Vector4f diffuse();
		Vector4f specular();
		float shininess();
		bool discardAlpha();
		float discardAlphaThreshold();

		Texture2D* getTexture2D(TextureType type);
		virtual void setTexture2D(TextureType textureType, const std::string& texture);
		virtual void setTexture2D(TextureType textureType, Texture2D* texture);
		bool hasDiffuse();
		bool hasSpecular();
		bool hasNormal();
		bool isTransParent();

		void setPostProcessShader(Shader*);
		Shader* postProcessShader();

		void updateProgram(Program* program);

	protected:
		Vector4f		myAmbient;
		Vector4f		myDiffuse;
		Vector4f		mySpecular;
		float			myShininess;
		TextureMap  myTextureMap;
		bool			myDiscardAlpha;
		float		   myDiscardAlphaThreshold;
		bool myIsTransparent;
		Shader* myShader;
	};
}
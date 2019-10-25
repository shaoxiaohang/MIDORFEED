#pragma once
#include <Core/Vector4f.h>
#include <map>
#include <string>
#include <vector>
namespace vrv
{
	class Texture2D;
	class Program;
   class StateSet;
   class Shader;

   class BuiltTexNameGenerator 
   {
   public:

      BuiltTexNameGenerator();

      std::string diffuseTexName();
      std::string specularTexName();
      std::string normalTexName();
   };

	class Material
	{
	public:

		typedef std::map<unsigned int, std::pair<std::string, Texture2D*>> TextureMap;
	public:
		Material();

		void setAmbient(Vector4f);
		void setDiffuse(Vector4f);
		void setSpecular(Vector4f);
		void setShininess(float);
		void setDiscardAlpha(bool);
		void setDiscardAlphaThreshold(float);
		void setTransparent(bool);
      void setStateSet(StateSet* state);
      StateSet* stateSet();

		Vector4f ambient();
		Vector4f diffuse();
		Vector4f specular();
		float shininess();
		bool discardAlpha();
		float discardAlphaThreshold();

      Program* program();

		void updateProgram();

      void setTexture(Texture2D* tex, const std::string& texName);

      void setBuiltInDiffuseTex(Texture2D* tex);
      void setBuiltInSpecularTex(Texture2D* tex);
      void setBuiltInNormalTex(Texture2D* tex);

      bool findNextAvailableSlot(int& slot);

      void setUseDiffuseTex(bool);
      void setUseSpecularTex(bool);
      void setUseNormalTex(bool);

      bool useDiffuseTex();
      bool useSpecularTex();
      bool useNormalTex();

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
      StateSet* myStateSet;
      std::vector<bool> myTextureSlotsMap;
      int myMaximumTextureUnit;
      bool myUseDiffuseTex;
      bool myUseSpecularTex;
      bool myUseNormalTex;
      BuiltTexNameGenerator myBuiltTexNameGenerator;
      bool myIsDirty;
	};
}
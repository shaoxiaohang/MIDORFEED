#include <Render/Material.h>
#include <Render/Texture2D.h>
#include <Render/Program.h>
#include <Render/OpenGLContext.h>
#include <Render/StateSet.h>
#include <Render/RenderState.h>

namespace vrv
{
   BuiltTexNameGenerator::BuiltTexNameGenerator()
   {}

   std::string BuiltTexNameGenerator::diffuseTexName()
   {
      return "vrv_material.diffuse_tex";
   }

   std::string BuiltTexNameGenerator::specularTexName()
   {
      return "vrv_material.specular_tex";
   }

   std::string BuiltTexNameGenerator::normalTexName()
   {
      return "vrv_material.normal_tex";
   }


   Material::Material()
      : myDiffuse(1, 1, 1, 1)
      , myAmbient(0.2, 0.2, 0.2, 1)
      , mySpecular(1, 1, 1, 1)
      , myShininess(64)
      , myDiscardAlpha(false)
      , myDiscardAlphaThreshold(0)
      , myIsTransparent(false)
      , myShader(0)
      , myStateSet(0)
      , myMaximumTextureUnit(16)
      , myUseDiffuseTex(false)
      , myUseSpecularTex(false)
      , myUseNormalTex(false)
   {
      myStateSet = new StateSet(new RenderState(), new Program("../data/shader/phoneLighting.vert",
         "../data/shader/phoneLighting.frag"));
      for (int i = 0; i < myMaximumTextureUnit; ++i)
      {
         myTextureSlotsMap.push_back(false);
      }
   }

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

   void Material::setStateSet(StateSet* state)
   {
      myStateSet = state;
   }

   StateSet* Material::stateSet()
   {
      return myStateSet;
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

   Program* Material::program()
   {
      if (myStateSet)
      {
         return myStateSet->program();
      }
      return 0;
   }

   void Material::setBuiltInDiffuseTex(Texture2D* tex)
   {
      setTexture(tex, myBuiltTexNameGenerator.diffuseTexName());
      myUseDiffuseTex = true;
   }

   void Material::setBuiltInSpecularTex(Texture2D* tex)
   {
      setTexture(tex, myBuiltTexNameGenerator.specularTexName());
      myUseSpecularTex = true;
   }

   void Material::setBuiltInNormalTex(Texture2D* tex)
   {
      setTexture(tex, myBuiltTexNameGenerator.normalTexName());
      myUseNormalTex = true;
   }

   bool Material::findNextAvailableSlot(int& slot)
   {
      for (int i = 0; i < myMaximumTextureUnit; ++i)
      {
         if (!myTextureSlotsMap[i])
         {
            slot = i;
            myTextureSlotsMap[i] = true;
            return true;
         }
      }

      VRV_ERROR("No texture unit available")
         return false;
   }

   void Material::setTexture(Texture2D* tex, const std::string& texName)
   {
      int unit = 0;
      if (findNextAvailableSlot(unit))
      {
         if (myTextureMap.find(unit) != myTextureMap.end())
         {
            VRV_ERROR("Texture unit already existed")
         }


         myTextureMap[unit] = std::make_pair(texName, tex);
      }
   }

   void Material::updateProgram()
   {
      Program* pro = program();
      if (pro)
      {
         pro->set("vrv_isTransparent", myIsTransparent);
         pro->set("vrv_discardAlpha", myDiscardAlpha);
         pro->set("vrv_discardAlphaThreshold", myDiscardAlphaThreshold);
         pro->set("vrv_material.hasDiffuse", myUseDiffuseTex);
         pro->set("vrv_material.hasSpecular", myUseSpecularTex);
         pro->set("vrv_material.hasNormal", myUseNormalTex);

         pro->set("vrv_material.ambient", myAmbient);
         pro->set("vrv_material.diffuse", myDiffuse);
         pro->set("vrv_material.specular", mySpecular);
         pro->set("vrv_material.shininess", myShininess);

         for (auto& tex : myTextureMap)
         {
            int id = tex.first;
            std::string name = tex.second.first;
            OpenGLContext::instance().glActiveTexture(GL_TEXTURE0 + id);
            OpenGLContext::instance().glBindTexture(GL_TEXTURE_2D, tex.second.second->id());
            pro->set(name, id);
         }
      }
   }

   void Material::setUseDiffuseTex(bool use)
   {
      myUseDiffuseTex = use;
   }

   void Material::setUseSpecularTex(bool use)
   {
      myUseSpecularTex = use;
   }

   void Material::setUseNormalTex(bool use)
   {
      myUseNormalTex = use;
   }

   bool Material::useDiffuseTex()
   {
      return myUseDiffuseTex;
   }

   bool Material::useSpecularTex()
   {
      return myUseSpecularTex;
   }

   bool Material::useNormalTex()
   {
      return myUseNormalTex;
   }
}
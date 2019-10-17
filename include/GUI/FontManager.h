#pragma once

#include <Render/OpenGLDefines.h>
#include <Core/Vector2f.h>
#include <Core/Singleton.h>
#include <unordered_map>

namespace vrv
{
   class Texture2D;

   class FontManager : public Singleton<FontManager>
   {
   public:

      struct CharacterMetric
      {
         Texture2D* myTexture;
         Vector2f mySize;
         Vector2f myBearing;
         GLuint myAdvance;
      };

      typedef std::unordered_map<char, CharacterMetric > CharacterMetricsMap;

      FontManager();

      void initialize();

      CharacterMetric metric(char c);

      CharacterMetricsMap characterMetricsMap();

   protected:

      CharacterMetricsMap myCharacterMetricsMap;

   };
}
#include <GUI/FontManager.h>
#include <Core/Utility.h>
#include <Render/OpenGLContext.h>
#include <Render/Node.h>
#include <Render/Texture2D.h>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace vrv
{
   FontManager* FontManager::myInstance = 0;

   FontManager::FontManager()
      : myFontRoot(0)
   {
      initialize();
   }

   FontManager::CharacterMetric FontManager::metric(char c)
   {
      return myCharacterMetricsMap[c];
   }
   
   FontManager::CharacterMetricsMap FontManager::characterMetricsMap()
   {
      return myCharacterMetricsMap;
   }

   void FontManager::setFontRoot(Node* node)
   {
      myFontRoot = node;
   }

   void FontManager::initialize()
   {
      FT_Library ft;

      if (FT_Init_FreeType(&ft))
      {
         VRV_ERROR("Failed to init freetype");
      }

      FT_Face face;
      if (FT_New_Face(ft, "../data/fonts/arial.ttf", 0, &face))
      {
         VRV_ERROR("Failed to load font");
      }

      FT_Set_Pixel_Sizes(face, 0, 48);

      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

      for (GLubyte c = 0; c < 128; ++c)
      {
         if (FT_Load_Char(face, c, FT_LOAD_RENDER))
         {
            VRV_ERROR("Failed to load font");
         }

         Texture2D* texture = new Texture2D(face->glyph->bitmap.width, face->glyph->bitmap.rows, Texture::RED);
         texture->setTextureWrapMode(Texture::CLAMP_TO_EDGE);
         texture->setTextureFilterMode(Texture::LINEAR);
         texture->fillData(face->glyph->bitmap.buffer);

         CharacterMetric metric = { texture, Vector2f(texture->width(),texture->height()), Vector2f(face->glyph->bitmap_left,face->glyph->bitmap_top),
        face->glyph->advance.x};

         myCharacterMetricsMap[c] = metric;
      }

      FT_Done_Face(face);
      FT_Done_FreeType(ft);

   }
}
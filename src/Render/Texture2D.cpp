#include <Render/Texture2D.h>
#include <Render/Image.h>
#include <Render/OpenGLContext.h>

namespace vrv
{
   Texture2D::Texture2D(int width, int height, TextureFormat textureFormat)
      : Texture(textureFormat)
   {
      myTextureType = GL_TEXTURE_2D;
      myWidth = width;
      myHeight = height;
      initialize();
   }

   Texture2D::Texture2D(const std::string& fileName)
   {
      myTextureType = GL_TEXTURE_2D;
      myImage = new Image(fileName);
      initialize();
   }

   Texture2D::Texture2D(Image* image)
   {
      myTextureType = GL_TEXTURE_2D;
      myImage = image;
     
   }

   bool Texture2D::hasAlphaChannel()
   {
      if (myImage && (myImage->pixelFormat() == Image::PF_RGBA || myImage->pixelFormat() == Image::PF_BGRA))
      {
         return true;
      }
   }

   void Texture2D::fillData(GLvoid* data)
   {
      bind();
      glTexImage2D(GL_TEXTURE_2D, 0, myInternelFormat, myWidth,
         myHeight, 0, myFormat, myDataType, data);
      unbind();
   }

   void Texture2D::initialize()
   {
      OpenGLContext& context = OpenGLContext::instance();
      glGenTextures(1, &myID);
      myTextureWrapMode = REPEAT;
      myTextureWrapModeGL = GL_REPEAT;
      myTextureFilterMode = LINEAR;
      myTextureFilterModeGL = GL_LINEAR;
      bind();
      if (myImage)
      {
         myInternelFormat = myImage->internalFormatGL();
         myWidth = myImage->width();
         myHeight = myImage->height();
         myFormat = myImage->pixelFormatGL();
         myDataType = myImage->dataTypeGL();

         context.glTexImage2D(GL_TEXTURE_2D, 0, myInternelFormat, myWidth,
            myHeight, 0, myFormat, myDataType, myImage->dataPointer());
      }
      else
      {
         switch (myTextureFormat)
         {
         case vrv::Texture::RED:
         {
            myInternelFormat = GL_RED;
            myFormat = GL_RED;
            myDataType = GL_UNSIGNED_BYTE;
         }
         break;
         case vrv::Texture::RGB:
         {
            myInternelFormat = GL_RGB;
            myFormat = GL_RGB;
            myDataType = GL_UNSIGNED_BYTE;
         }
         break;
         case vrv::Texture::RGBA:
         {
            myInternelFormat = GL_RGBA;
            myFormat = GL_RGBA;
            myDataType = GL_UNSIGNED_BYTE;
         }
         break;
         case vrv::Texture::FLOAT16:
         {
            myInternelFormat = GL_RGBA16F;
            myFormat = GL_RGBA;
            myDataType = GL_FLOAT;
         }
         break;
         case vrv::Texture::FLOAT32:
         {
            myInternelFormat = GL_RGBA32F;
            myFormat = GL_RGBA;
            myDataType = GL_FLOAT;
         }
         break;
         default:
            break;
         }


         context.glTexImage2D(GL_TEXTURE_2D, 0, myInternelFormat, myWidth,
            myHeight, 0, myFormat, myDataType, 0);
      }

      context.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      context.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      context.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, myTextureFilterModeGL);
      context.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, myTextureFilterModeGL);

      if (myGenerateMipmap)
      {
         //context.glGenerateMipmap(GL_TEXTURE_2D);
      }
      
      unbind();
   }

   void Texture2D::update()
   {
      OpenGLContext& context = OpenGLContext::instance();

      bind();
      context.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, myTextureWrapModeGL);
      context.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, myTextureWrapModeGL);
      if (myTextureWrapMode == CLAMP_TO_BORDER)
      {
         float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
         glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
      }
      context.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, myTextureFilterModeGL);
      context.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, myTextureFilterModeGL);
      unbind();
   }
}
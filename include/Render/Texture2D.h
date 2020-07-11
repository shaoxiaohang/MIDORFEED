#pragma once

#include <string>
#include <Render/Texture.h>
#include <Render/OpenGLDefines.h>

namespace vrv {

  class Image;
  class Texture2D : public Texture {
  public:
    Texture2D(int width, int height, TextureFormat textureFormat);
    Texture2D(const std::string& fileName);
    Texture2D(Image* image);
    bool hasAlphaChannel();

    void fillData(GLvoid* data);


  protected:
    void initialize();
    void update();
  };
}
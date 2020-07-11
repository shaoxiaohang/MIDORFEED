#include <Render/Image.h>
#include <Core/Utility.h>
#include <windows.h>
#include <Render/OpenGLContext.h>
#include <Render/stb_image.h>

namespace vrv
{
  Image::Image(const std::string& file)
    : myFileName(file)
    , myWidth(0)
    , myHeight(0)
  {
    initialize();
  }

  unsigned int Image::width()
  {
    return myWidth;
  }

  unsigned int Image::height()
  {
    return myHeight;
  }

  unsigned int Image::internalFormatGL()
  {
    return myInternalFormatGL;
  }

  unsigned int Image::pixelFormatGL()
  {
    return myPixelFormatGL;
  }

  unsigned int Image::dataTypeGL()
  {
    return myDataTypeGL;
  }

  unsigned char* Image::dataPointer()
  {
    return image_data_;
  }

  Image::ImagePixelFormat Image::pixelFormat()
  {
    return myPixelFormat;
  }

  void Image::initialize()
  {
    int channel;
    image_data_ = stbi_load(myFileName.c_str(), &myWidth, &myHeight, &channel, 0);
    if (!image_data_)
    {
      VRV_ERROR("Failed to open image" + myFileName)
    }

    myInternalFormat = IF_RGB;
    myInternalFormatGL = GL_RGB;
    myPixelFormat = PF_RGB;
    myPixelFormatGL = GL_RGB;
    myDataType = UNSIGNED_BYTE;
    myDataTypeGL = GL_UNSIGNED_BYTE;
  }
}
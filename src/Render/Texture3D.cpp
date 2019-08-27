#include <Render/Texture3D.h>
#include <Render/Image.h>
#include <Render/OpenGLContext.h>
#include <Core/Utility.h>

namespace vrv
{
	Texture3D::Texture3D(const std::vector<std::string>& names)
		: myImageNames(names)
	{
		myTextureType = GL_TEXTURE_CUBE_MAP;
		initialize();
	}

	bool Texture3D::hasAlphaChannel()
	{
		return true;
	}

	void Texture3D::initialize()
	{
		glGenTextures(1, &myID);
		
		myTextureWrapMode = CLAMP_TO_EDGE;
		myTextureWrapModeGL = GL_CLAMP_TO_EDGE;
		myTextureFilterMode = LINEAR;
		myTextureFilterModeGL = GL_LINEAR;

		if (myImageNames.size() != 6)
		{
			VRV_ERROR("Need 6 images in cube map")
			return;
		}

		bind();

		for (int i = 0; i < 6; ++i)
		{
			Image* image = new Image(myImageNames[i]);
			if (image)
			{
				myImages.push_back(image);
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
					image->internalFormatGL(), image->width(), image->height(), 0, image->pixelFormatGL(),
					image->dataTypeGL(), image->dataPointer());
			}
			else
			{
				VRV_ERROR(myImageNames[i] + "failed to load\n")
			}
		}

		glTexParameteri(myTextureType, GL_TEXTURE_WRAP_S, myTextureWrapModeGL);
		glTexParameteri(myTextureType, GL_TEXTURE_WRAP_T, myTextureWrapModeGL);
		glTexParameteri(myTextureType, GL_TEXTURE_WRAP_R, myTextureWrapModeGL);

		glTexParameteri(myTextureType, GL_TEXTURE_MIN_FILTER, myTextureFilterModeGL);
		glTexParameteri(myTextureType, GL_TEXTURE_MAG_FILTER, myTextureFilterModeGL);

		unbind();

	}

	void Texture3D::update()
	{

	}
}
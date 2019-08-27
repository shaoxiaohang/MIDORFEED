#pragma once

#include <Render/Texture.h>
#include <vector>
namespace vrv
{
	class FrameBuffer;
	class Texture2D;

	class FrameBufferAttachment
	{
	public:
		enum Type
		{
			Texture,
			RenderBuffer
		};

		enum Target
		{
			Color,
			Depth,
			Depth_Stencil
		};

		enum RenderBufferFormat
		{
			DEPTH24_STENCIL8
		};

		FrameBufferAttachment(int width, int height, Type type, Target target, Texture::TextureFormat textureFormat, int 
      index = 0);
		FrameBufferAttachment(int width, int height, Type type, Target target, RenderBufferFormat renderBufferFormat,
      int index = 0);

		void attachToFrameBuffer(FrameBuffer* frameBuffer);
		
		void setColorAttachmentIndex(unsigned int index);
		unsigned int colorAttachmentIndex();

		Type type();
		Target target();
		RenderBufferFormat renderBufferFormat();
		Texture::TextureFormat textureFormat();

		Texture2D* textureBuffer();

	protected:
		unsigned int generateRenderBuffer(RenderBufferFormat format, int width, int height);

	protected:
		Type myType;
		Target myTarget;
		RenderBufferFormat myRenderBufferFormat;
		Texture::TextureFormat myTextureFormat;
		int myColorAttachmentIndex;
		int myWidth;
		int myHeight;
		Texture2D* myTextureBuffer;
		unsigned int myRenderBuffer;
	};


	class Texture2D;
	class FrameBuffer
	{
	public:
		FrameBuffer(int width, int height);
		~FrameBuffer();
		void bind();
		void unbind();
		void initialize();
		void addAttachment(FrameBufferAttachment* attachment);
		void addAttachment(FrameBufferAttachment* attachment, int index);

		FrameBufferAttachment* getColorAttachment(int index);

		Texture2D* textureBuffer();
		Texture2D* textureBuffer(int index);

	protected:
		unsigned int myID;
		std::vector<FrameBufferAttachment*> myAttachments;
	};
}
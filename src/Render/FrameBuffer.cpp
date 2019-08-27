#include <Render/FrameBuffer.h>
#include <Render/Texture2D.h>
#include <Render/OpenGLContext.h>
#include <Core/Utility.h>
namespace vrv
{
	FrameBufferAttachment::FrameBufferAttachment(int width, int height,
		Type type, Target target, Texture::TextureFormat textureFormat, int
		index)
		: myWidth(width)
		, myHeight(height)
		, myType(type)
		, myTarget(target)
		, myTextureFormat(textureFormat)
		, myColorAttachmentIndex(index)
		, myTextureBuffer(0)
		, myRenderBuffer(-1)
	{
		myTextureBuffer = new Texture2D(myWidth, myHeight, myTextureFormat);
	}

	FrameBufferAttachment::FrameBufferAttachment(int width, int height,
		Type type, Target target, RenderBufferFormat renderBufferFormat, int
		index)
		: myWidth(width)
		, myHeight(height)
		, myType(type)
		, myTarget(target)
		, myRenderBufferFormat(renderBufferFormat)
		, myTextureBuffer(0)
		, myRenderBuffer(-1)
		, myColorAttachmentIndex(index)
	{
		myRenderBuffer = generateRenderBuffer(myRenderBufferFormat, myWidth, myHeight);
	}

	void FrameBufferAttachment::attachToFrameBuffer(FrameBuffer* frameBuffer)
	{
		switch (myTarget)
		{
		case vrv::FrameBufferAttachment::Color:
		{
			if (myType == Texture)
			{
            OpenGLContext::instance().glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + myColorAttachmentIndex,
					GL_TEXTURE_2D, myTextureBuffer->id(), 0);
			}
			else if (myType == RenderBuffer)
			{
            OpenGLContext::instance().glFramebufferRenderbuffer(GL_FRAMEBUFFER,
					GL_COLOR_ATTACHMENT0 + myColorAttachmentIndex, GL_RENDERBUFFER, myRenderBuffer);
			}
		}
		break;
		case vrv::FrameBufferAttachment::Depth:
		{
			if (myType == Texture)
			{
            OpenGLContext::instance().glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
					GL_TEXTURE_2D, myTextureBuffer->id(), 0);
			}
			else if (myType == RenderBuffer)
			{
            OpenGLContext::instance().glFramebufferRenderbuffer(GL_FRAMEBUFFER,
					GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, myRenderBuffer);
			}
		}
		break;
		case vrv::FrameBufferAttachment::Depth_Stencil:
		{
			if (myType == Texture)
			{
            OpenGLContext::instance().glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
					GL_TEXTURE_2D, myTextureBuffer->id(), 0);
			}
			else if (myType == RenderBuffer)
			{
            OpenGLContext::instance().glFramebufferRenderbuffer(GL_FRAMEBUFFER,
					GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, myRenderBuffer);
			}
		}
		break;
		default:
			break;
		}
	}

	void FrameBufferAttachment::setColorAttachmentIndex(unsigned int index)
	{
		myColorAttachmentIndex = index;
	}

	unsigned int FrameBufferAttachment::colorAttachmentIndex()
	{
		return myColorAttachmentIndex;
	}

	FrameBufferAttachment::Type FrameBufferAttachment::type()
	{
		return myType;
	}

	FrameBufferAttachment::Target FrameBufferAttachment::target()
	{
		return myTarget;
	}

	FrameBufferAttachment::RenderBufferFormat FrameBufferAttachment::renderBufferFormat()
	{
		return myRenderBufferFormat;
	}

	Texture::TextureFormat FrameBufferAttachment::textureFormat()
	{
		return myTextureFormat;
	}

	Texture2D* FrameBufferAttachment::textureBuffer()
	{
		return myTextureBuffer;
	}

	unsigned int FrameBufferAttachment::generateRenderBuffer(RenderBufferFormat format, int width, int height)
	{
		unsigned int renderBuffer;
		unsigned int renderBufferFormat;
		switch (format)
		{
		case vrv::FrameBufferAttachment::DEPTH24_STENCIL8:
			renderBufferFormat = GL_DEPTH24_STENCIL8;
			break;
		default:
			break;
		}
      OpenGLContext::instance().glGenRenderbuffers(1, &renderBuffer);
      OpenGLContext::instance().glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
      OpenGLContext::instance().glRenderbufferStorage(GL_RENDERBUFFER, renderBufferFormat, width, height);
      OpenGLContext::instance().glBindRenderbuffer(GL_RENDERBUFFER, 0);

		return renderBuffer;
	}

	FrameBuffer::FrameBuffer(int width, int height)
	{
      OpenGLContext::instance().glGenFramebuffers(1, &myID);
	}

	FrameBuffer::~FrameBuffer()
	{
      OpenGLContext::instance().glDeleteFramebuffers(1, &myID);
	}

	void FrameBuffer::bind()
	{
      OpenGLContext::instance().glBindFramebuffer(GL_FRAMEBUFFER, myID);
	}

	void FrameBuffer::unbind()
   {
      OpenGLContext::instance().glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::initialize()
	{
		bind();

		int numOfColorAttachments = 0;
		for (unsigned int i = 0; i < myAttachments.size(); ++i)
		{
			if (myAttachments[i]->type() == FrameBufferAttachment::Texture)
			{
				numOfColorAttachments++;
			}
			myAttachments[i]->attachToFrameBuffer(this);
		}
		unsigned int* attchments = new unsigned int(numOfColorAttachments);
		for (int i = 0; i < numOfColorAttachments; ++i)
		{
			attchments[i] = GL_COLOR_ATTACHMENT0 + i;
		}
      OpenGLContext::instance().glDrawBuffers(numOfColorAttachments, attchments);

		if (OpenGLContext::instance().glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			VRV_ERROR("frame buffer is not completed")
		}

		unbind();
	}

	void FrameBuffer::addAttachment(FrameBufferAttachment* attachment)
	{
		myAttachments.push_back(attachment);
	}

	void FrameBuffer::addAttachment(FrameBufferAttachment* attachment, int index)
	{
		attachment->setColorAttachmentIndex(index);
		myAttachments.push_back(attachment);
	}

	FrameBufferAttachment* FrameBuffer::getColorAttachment(int index)
	{
		for (unsigned int i = 0; i < myAttachments.size(); ++i)
		{
			FrameBufferAttachment* attachment = myAttachments[i];
			if (attachment->target() == FrameBufferAttachment::Color
				&& attachment->colorAttachmentIndex() == index)
			{
				return attachment;
			}
		}

		return 0;
	}

	Texture2D* FrameBuffer::textureBuffer()
	{
		return textureBuffer(0);
	}

	Texture2D* FrameBuffer::textureBuffer(int index)
	{
		for (unsigned int i = 0; i < myAttachments.size(); ++i)
		{
			FrameBufferAttachment* attachment = myAttachments[i];
			if (attachment->target() == FrameBufferAttachment::Color
				&& attachment->colorAttachmentIndex() == index)
			{
				return attachment->textureBuffer();
			}
		}

		return 0;
	}
}
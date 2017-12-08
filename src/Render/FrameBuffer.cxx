#include <Render/FrameBuffer.h>
#include <Render/QtContext.h>
#include <Render/Texture2D.h>
#include <Core/Utility.h>
namespace vrv
{
	FrameBuffer::FrameBuffer(int width, int height)
	{
		QtContext::instance().glGenFramebuffers(1, &myID);
		QtContext::instance().glBindFramebuffer(GL_FRAMEBUFFER, myID);
		myTextureBuffer = new Texture2D(width, height);
		QtContext::instance().glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, myTextureBuffer->id(), 0);
		
		int type = FrameBuffer::DEPTH_STENCIL;

		unsigned int renderBuffer;
		unsigned int renderBufferType;
		QtContext::instance().glGenRenderbuffers(1, &renderBuffer);
		switch (type)
		{
		case vrv::FrameBuffer::DEPTH:
			renderBufferType = GL_DEPTH;
			break;
		case vrv::FrameBuffer::STENCIL:
			renderBufferType = GL_STENCIL;
			break;
		case vrv::FrameBuffer::DEPTH_STENCIL:
			renderBufferType = GL_DEPTH24_STENCIL8;
			break;
		default:
			break;
		}
		QtContext::instance().glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
		QtContext::instance().glRenderbufferStorage(GL_RENDERBUFFER, renderBufferType, width, height);
		QtContext::instance().glBindRenderbuffer(GL_RENDERBUFFER, 0);
		QtContext::instance().glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);

		if (QtContext::instance().glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			VRV_ERROR("frame buffer is not completed")
		}
		QtContext::instance().glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	FrameBuffer::~FrameBuffer()
	{
		QtContext::instance().glDeleteFramebuffers(1, &myID);
	}

	void FrameBuffer::bind()
	{
		QtContext::instance().glBindFramebuffer(GL_FRAMEBUFFER, myID);
	}

	void FrameBuffer::unbind()
	{
		if (QtContext::instancePtr())
		{
			QtContext::instance().glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		else
		{
			int as = 3;
		}

	}

	int FrameBuffer::textureID()
	{
		return myTextureBuffer->id();
	}
}
#pragma once
namespace vrv
{
	class Texture2D;
	class FrameBuffer
	{
	public:
		enum AttachmentType
		{
			COLOR,
			DEPTH,
			STENCIL,
			DEPTH_STENCIL
		};

		FrameBuffer(int x, int y);
		~FrameBuffer();
		void bind();
		void unbind();
		int textureID();

	protected:
		unsigned int myID;
		Texture2D* myTextureBuffer;
	};
}
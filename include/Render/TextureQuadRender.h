#pragma once

namespace vrv
{
	class Geometry;
	class DrawState;
	class Texture2D;

	class TextureQuadRender
	{
	public:
		TextureQuadRender();

		void drawTexture(Texture2D*);

	protected:
		void initialize();

	protected:
		Geometry* myQuadGeometry;
		DrawState* myDrawState;
	};
}
#pragma once

namespace vrv
{
	class Drawable;
	class RenderState;
	class Context
	{
	public:
		Context();
		void draw(Drawable* renderState);
		void forceSynRenderState();

	protected:
		RenderState* myCachedRenderState;
	};
}
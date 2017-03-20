#pragma once

namespace vrv
{
	class Drawable;
	class RenderState;
	class ClearState;
	class Context
	{
	public:
		Context();
		void draw(Drawable* renderState);
		void forceSynGL();
		void clear(ClearState* clear);
	protected:
		RenderState* myCachedRenderState;
		ClearState* myCachedClearState;
	};
}
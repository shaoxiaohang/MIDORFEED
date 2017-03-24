#pragma once

namespace vrv
{
	class Drawable;
	class RenderState;
	class ClearState;
	class MainWindow;
	class Context
	{
	public:
		Context();
		void draw(Drawable* renderState);
		void forceSynGL();
		void clear(ClearState* clear);
		virtual void initialize() = 0;
	protected:
		RenderState* myCachedRenderState;
		ClearState* myCachedClearState;
	};
}
#pragma once

namespace vrv
{
	class Drawable;
	class RenderState;
	class ClearState;
	class MainWindow;
	class Scene;
	class Context
	{
	public:
		Context();
		void draw(Drawable* renderState);
		void forceSynGL();
		void clear(ClearState* clear);
		virtual void initialize() = 0;
		void setScene(Scene* scene);
	protected:
		RenderState* myCachedRenderState;
		ClearState* myCachedClearState;
		Scene* myScene;
	};
}
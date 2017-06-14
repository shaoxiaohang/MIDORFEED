#pragma once

namespace vrv
{
	class RenderInfo;
	class RenderState;
	class ClearState;
	class MainWindow;
	class Scene;
	class Context
	{
	public:
		Context();
		void draw(RenderInfo& renderInfo);
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
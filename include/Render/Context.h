#pragma once

namespace vrv
{
	class RenderInfo;
	class RenderState;
	class ClearState;
	class MainWindow;
	class Scene;
	class DrawState;
	class Context
	{
	public:
		Context();
		void draw(RenderInfo& renderInfo ,DrawState* drawState);
		void forceSynGL();
		void clear(ClearState* clear);
		virtual void initialize() = 0;
		void setScene(Scene* scene);
	protected:
		Scene* myScene;
	};
}
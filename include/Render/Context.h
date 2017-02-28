#pragma once

namespace vrv
{
	class RenderState;
	class Context
	{
	public:
		Context();
		void draw(const RenderState& renderState);
		void forceSynRenderState();

	protected:
		RenderState* myCachedRenderState;
	};
}
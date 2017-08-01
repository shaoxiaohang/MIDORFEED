#pragma once

#include <Core/Vector4.h>
namespace vrv
{
	class ClearState
	{
	public:
		enum ClearMask
		{
			COLOR_BUFFER_BIT,
			DEPTH_BUFFER_BIT,
			DEPTH_COLOR_BIT,
			DEPTH_COLOR_STENCIL_BIT
		};
	public:
		ClearState();

		void apply();
		void applyIfChanged(const ClearState& state); 

		Vector4f clearColor() const;
		void setClearColor(Vector4f color);

		float clearDepth() const;
		void setClearDepth(float depth);

		void clear();

	protected:
		Vector4f myClearColor;
		float myClearDepth;
		ClearMask myClearMask;
		unsigned int myGLClearMask;
	};
}
#pragma once

#include <Core/Vector4.h>
namespace vrv
{
	class ClearState
	{
	public:
		ClearState();

		void apply();
		void applyIfChanged(const ClearState& state); 

		Vector4f clearColor() const;
		void setClearColor(Vector4f color);

		float clearDepth() const;
		void setClearDepth(float depth);

	protected:
		Vector4f myClearColor;
		float myClearDepth;
	};
}
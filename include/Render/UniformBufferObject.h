#pragma once

#include <Render/BufferObject.h>
#include <vector>
namespace vrv
{
	class AutomaticUniform;

	class UniformBufferObject : public BufferObject
	{
	public:
		UniformBufferObject();

		void bindToPoint(int point);

		void addAutomaticUniform(AutomaticUniform* uniform);

		void build();

		void update();

	protected:
		std::vector<AutomaticUniform*> myUniforms;
	};
}
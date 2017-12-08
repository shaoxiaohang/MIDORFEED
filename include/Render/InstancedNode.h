#pragma once

#include <Core/Node.h>
#include <Core/Vector3.h>
#include <Render/Array.h>
#include <vector>
namespace vrv
{
	class InstancedNode : public Node
	{
	public:
		InstancedNode(const std::string& name, int count, const std::vector<Vector3f>& offset, const std::vector<float>&
			scales);
		void setUpInstanced();

	protected:
		int myCount;
		std::vector<Vector3f> myOffsets;
		std::vector<float> myScales;
		ArrayVec3 myMatrices;
	};
}
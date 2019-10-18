#include <Render/InstancedNode.h>
#include <Render/Drawable.h>
#include <Render/StateSet.h>
#include <Render/VertexArrayObject.h>
#include <Render/Geometry.h>
namespace vrv
{
	InstancedNode::InstancedNode(const std::string& name, int count,
		const std::vector<Vector3f>& offset, const std::vector<float>& scales)
		: Node(name)
		, myCount(count)
		, myOffsets(offset)
		, myScales(scales)
	{
		for (int i = 0; i < myCount; i++)
		{
			myMatrices.add(myOffsets[i]);
		}
	}

	void InstancedNode::setUpInstanced()
	{
		for (int i = 0; i < numberOfDrawable(); i++)
		{
			Drawable* drawable = getDrawable(i);
			Geometry* geometry = dynamic_cast<Geometry*>(drawable);
			//geometry->setInstancedMatrices(&myMatrices);
			//geometry->setInstancedCount(myMatrices.size());
		}
	}
}
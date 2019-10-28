#pragma once

#include <Core/Vector3f.h>
#include <Render/Geometry.h>
namespace vrv
{
	class Geometry;
	class BoxTessellator
	{
	public:
		static Geometry* compute(Vector3f radius)
		{
			Geometry* cube = new Geometry();
			ArrayVec3* pos = new ArrayVec3(8);
			Vector3f corner = radius * 0.5;
			pos->add(Vector3f(corner.x(),-corner.y(), corner.z()));
			pos->add(Vector3f(corner.x(), corner.y(), corner.z()));
			pos->add(Vector3f(corner.x(), -corner.y(), -corner.z()));
			pos->add(Vector3f(corner.x(), corner.y(), -corner.z()));
			pos->add(Vector3f(-corner.x(), -corner.y(), corner.z()));
			pos->add(Vector3f(-corner.x(), corner.y(), corner.z()));
			pos->add(Vector3f(-corner.x(), -corner.y(), -corner.z()));
			pos->add(Vector3f(-corner.x(), corner.y(), -corner.z()));
			ArrayUnsignedInt* indexes = new ArrayUnsignedInt(36);
			//top
			indexes->add(0);
			indexes->add(7);
			indexes->add(4);
			indexes->add(4);
			indexes->add(7);
			indexes->add(5);
			//bottom
			indexes->add(2);
			indexes->add(3);
			indexes->add(6);
			indexes->add(6);
			indexes->add(3);
			indexes->add(7);
			//left
			indexes->add(4);
			indexes->add(6);
			indexes->add(2);
			indexes->add(4);
			indexes->add(2);
			indexes->add(0);
			//right
			indexes->add(1);
			indexes->add(3);
			indexes->add(7);
			indexes->add(1);
			indexes->add(7);
			indexes->add(5);
			//front
			indexes->add(0);
			indexes->add(2);
			indexes->add(1);
			indexes->add(1);
			indexes->add(2);
			indexes->add(3);
			//back
			indexes->add(5);
			indexes->add(7);
			indexes->add(6);
			indexes->add(5);
			indexes->add(6);
			indexes->add(4);

			cube->addVertexAttribute(0, pos);
			cube->addVertexIndex(indexes);

			return cube;
		}
	};

}
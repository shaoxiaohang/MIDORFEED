#include <Render/Tessellation.h>
#include <Render/Geometry.h>
#include <Core/Utility.h>
#include <vector>
namespace vrv
{
	void SubdivisionSphereTessellatorSimple::compute(ArrayVec3& positions, ArrayUnsignedInt& indexes, 
		int numberOfSubdivisions)
	{
		Geometry* ellipsoid = new Geometry();
		positions.resize(numberOfVertices(numberOfSubdivisions));
		indexes.resize(3 * numberOfTriangles(numberOfSubdivisions));
		static Vector3f p0 = Vector3f(0, 0, 1);
		static Vector3f p1 = Vector3f(0, 2.0f*Utility::sqrt(2) / 3.0f, -1.0f / 3.0f);
		static Vector3f p2 = Vector3f(-Utility::sqrt(6) / 3.0f, -Utility::sqrt(2) / 3.0f, -1.0f / 3.0f);
		static Vector3f p3 = Vector3f(Utility::sqrt(6) / 3.0f, -Utility::sqrt(2) / 3.0f, -1.0f / 3.0f);

		p0 = p0 * Vector3f(1, 1, 1.2f);
		p1 = p1 * Vector3f(1, 1, 1.2f);
		p2 = p2 * Vector3f(1, 1, 1.2f);
		p3 = p3 * Vector3f(1, 1, 1.2f);

		positions.add(p0);
		positions.add(p1);
		positions.add(p2);
		positions.add(p3);
		subdivide(positions, indexes, Vector3f(0, 1, 2), numberOfSubdivisions);
		subdivide(positions, indexes, Vector3f(0, 2, 3), numberOfSubdivisions);
		subdivide(positions, indexes, Vector3f(0, 3, 1), numberOfSubdivisions);
		subdivide(positions, indexes, Vector3f(1, 3, 2), numberOfSubdivisions);
	}

	void SubdivisionSphereTessellatorSimple::subdivide(ArrayVec3& positions, ArrayUnsignedInt& indexes, Vector3f currenctFace,
		int numberOfSubdivisions)
	{
		int p0 = currenctFace.x();
		int p1 = currenctFace.y();
		int p2 = currenctFace.z();
		if (numberOfSubdivisions > 0)
		{
			Vector3f v0 = positions[p0];
			Vector3f v1 = positions[p1];
			Vector3f v2 = positions[p2];

			Vector3f v01 = (v0 + v1) / 2;
			Vector3f v12 = (v1 + v2) / 2;
			Vector3f v20 = (v0 + v2) / 2;

			v01 = v01.normalizedVector();
			v12 = v12.normalizedVector();
			v20 = v20.normalizedVector();

			v01 = v01 * Vector3f(1, 1, 1.2f);
			v12 = v12 * Vector3f(1, 1, 1.2f);
			v20 = v20 * Vector3f(1, 1, 1.2f);

			positions.add(v01);
			positions.add(v12);
			positions.add(v20);

			int p01 = positions.size() - 3;
			int p12 = positions.size() - 2;
			int p20 = positions.size() - 1;
			
			//decrease the division
			numberOfSubdivisions--;

			//p0 p01 p20
			subdivide(positions, indexes, Vector3f(p0, p01, p20), numberOfSubdivisions);
			//p01 p1 p12
			subdivide(positions, indexes, Vector3f(p01, p1, p12), numberOfSubdivisions);
			//p01 p12 p20
			subdivide(positions, indexes, Vector3f(p01, p12, p20), numberOfSubdivisions);
			//p20 p12 p2
			subdivide(positions, indexes, Vector3f(p20, p12, p2), numberOfSubdivisions);
		}
		else
		{
			indexes.add(p0);
			indexes.add(p1);
			indexes.add(p2);
		}
	}

	int SubdivisionSphereTessellatorSimple::numberOfVertices(int numberOfSubdivisions)
	{
		int numberOfVertices = 0;
		for (int i = 0; i < numberOfSubdivisions; ++i)
		{
			numberOfVertices += Utility::powi(4, i);
		}
		numberOfVertices = 4 + (12 * numberOfVertices);
		return numberOfVertices;
	}

	int SubdivisionSphereTessellatorSimple::numberOfTriangles(int numberOfSubdivisions)
	{
		int numberOfTriangles = 0;
		for (int i = 0; i <= numberOfSubdivisions; ++i)
		{
         numberOfTriangles += Utility::powi(4, i);
		}
		numberOfTriangles *= 4;

		return numberOfTriangles;
	}

	void GeographicGridTessellation::compute(ArrayVec3& positions, ArrayUnsignedInt& indexes,
		ArrayVec3& normals, ArrayVec2& sts, int numberOfStacks, int numberOfSlices, float a, float b, float c)
	{
		int vertices = numberOfVertices(numberOfStacks, numberOfSlices);
		int traingles = numberOfTriangles(numberOfStacks, numberOfSlices);
		positions.resize(vertices);
		normals.resize(vertices);
		indexes.resize(3 * traingles);

		std::vector<Vector2f> lookupTable;
		for (int j = 0; j < numberOfSlices; ++j)
		{
			float theta = 360.0f / numberOfSlices;
			float cosTheta = Utility::cos(theta * j);
			float sinTheta = Utility::sin(theta * j);
			lookupTable.push_back(Vector2f(cosTheta, sinTheta));
		}

		//First calcualte positions

		//top point
		positions.add(Vector3f(0, 0, c));

		//mid points
		for (int i = 1; i < numberOfStacks; ++i)
		{
			float phi = 180.0f / numberOfStacks;
			float sinPhi = Utility::sin(phi * i);
			float cosPhi = Utility::cos(phi * i);
			for (int j = 0; j < numberOfSlices; ++j)
			{
				float theta = 360.0f / numberOfSlices;
				float cosTheta = lookupTable[j].x();
				float sinTheta = lookupTable[j].y();
				positions.add(Vector3f(a*cosTheta*sinPhi, b*sinTheta*sinPhi, c*cosPhi));
			}
		}

		//bottom point
		positions.add(Vector3f(0, 0, -c));

		for (unsigned i = 0; i < positions.size(); ++i)
		{
			Vector3f position = positions[i];
			Vector3f normal = Vector3f(position.x() / a*a, position.y() / b*b, position.z() / c*c);
			normal.normalize();
			normals.add(normal);

			Vector2f st;
			st.x() = Utility::atan2(normal.y(), normal.x()) / Utility::twoPI + 0.5f;
			st.y() = Utility::asin(normal.z()) / Utility::PI + 0.5f;
			sts.add(st);
		}

		//Calculate indexes

		//top triangles fans
		for (int i = 1; i < numberOfSlices; ++i)
		{
			indexes.add(0);
			indexes.add(i);
			indexes.add(i + 1);
		}
		indexes.add(0);
		indexes.add(numberOfSlices);
		indexes.add(1);

		//mid triangles strips
		for (int i = 0; i < numberOfStacks - 2; ++i)
		{
			for (int j = 0; j < numberOfSlices - 1; ++j)
			{
				int vertice1 = numberOfSlices* i + j + 1;
				int vertice2 = vertice1 + 1;
				int vertice3 = numberOfSlices* (i+1) + j + 1;
				int vertice4 = vertice3 + 1;

				indexes.add(vertice3);
				indexes.add(vertice4);
				indexes.add(vertice2);

				indexes.add(vertice3);
				indexes.add(vertice2);
				indexes.add(vertice1);
			}

			int vertice1 = numberOfSlices*i + numberOfSlices;
			int vertice2 = numberOfSlices*i + 1;
			int vertice3 = numberOfSlices*(i+1) + numberOfSlices;
			int vertice4 = numberOfSlices*(i+1) + 1;

			indexes.add(vertice3);
			indexes.add(vertice4);
			indexes.add(vertice2);

			indexes.add(vertice3);
			indexes.add(vertice2);
			indexes.add(vertice1);
		}
		
		int lastPosition = vertices - 1;
		//bottom triangles fans
		for (int i = 1; i < numberOfSlices; ++i)
		{
			indexes.add(lastPosition);
			indexes.add(lastPosition - numberOfSlices + i);
			indexes.add(lastPosition - numberOfSlices + i - 1);
		}
		indexes.add(lastPosition);
		indexes.add(lastPosition - numberOfSlices);
		indexes.add(lastPosition - 1);
	}

	int GeographicGridTessellation::numberOfVertices(int numberOfStacks, int numberOfSlices)
	{
		return 2 + numberOfSlices * (numberOfStacks - 1);
	}

	int GeographicGridTessellation::numberOfTriangles(int numberOfStacks, int numberOfSlices)
	{
		int topTriangles = numberOfSlices;
		int botTriangels = numberOfSlices;
		int midTriangles = numberOfSlices * (numberOfStacks - 2) * 2;
		return topTriangles + botTriangels + midTriangles;
	}
}
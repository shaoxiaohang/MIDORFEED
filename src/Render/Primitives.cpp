#include <Render/Primitives.h>
#include <Render/Tessellation.h>
namespace vrv
{
	bool Cube::myGeometryInitialized = false;
	ArrayVec3 Cube::sPosArray = ArrayVec3(36);
	ArrayVec2 Cube::sTexArray = ArrayVec2(36);
	ArrayVec3 Cube::sNormalArray = ArrayVec3(36);

	Cube::Cube()
	{
		if (!myGeometryInitialized)
		{
			sPosArray.add( Vector3f(-0.5f, -0.5f, -0.5f));
			sPosArray.add(Vector3f(0.5f, -0.5f, -0.5f));
			sPosArray.add(Vector3f(0.5f, 0.5f, -0.5f));
			sPosArray.add(Vector3f(0.5f, 0.5f, -0.5f));
			sPosArray.add(Vector3f(-0.5f, 0.5f, -0.5f));
			sPosArray.add(Vector3f(-0.5f, -0.5f, -0.5f));

			sPosArray.add(Vector3f(-0.5f, -0.5f, 0.5f));
			sPosArray.add(Vector3f(0.5f, -0.5f, 0.5f));
			sPosArray.add(Vector3f(0.5f, 0.5f, 0.5f));
			sPosArray.add(Vector3f(0.5f, 0.5f, 0.5f));
			sPosArray.add(Vector3f(-0.5f, 0.5f, 0.5f));
			sPosArray.add(Vector3f(-0.5f, -0.5f, 0.5f));
	
			sPosArray.add(Vector3f(-0.5f, 0.5f, 0.5f));
			sPosArray.add(Vector3f(-0.5f, 0.5f, -0.5f));
			sPosArray.add(Vector3f(-0.5f, -0.5f, -0.5f));
			sPosArray.add(Vector3f(-0.5f, -0.5f, -0.5f));
			sPosArray.add(Vector3f(-0.5f, -0.5f, 0.5f));
			sPosArray.add(Vector3f(-0.5f, 0.5f, 0.5f));

			sPosArray.add(Vector3f(0.5f, 0.5f, 0.5f));
			sPosArray.add(Vector3f(0.5f, 0.5f, -0.5f));
			sPosArray.add(Vector3f(0.5f, -0.5f, -0.5f));
			sPosArray.add(Vector3f(0.5f, -0.5f, -0.5f));
			sPosArray.add(Vector3f(0.5f, -0.5f, 0.5f));
			sPosArray.add(Vector3f(0.5f, 0.5f, 0.5f));

			sPosArray.add(Vector3f(-0.5f, -0.5f, -0.5f));
			sPosArray.add(Vector3f(0.5f, -0.5f, -0.5f));
			sPosArray.add(Vector3f(0.5f, -0.5f, 0.5f));
			sPosArray.add(Vector3f(0.5f, -0.5f, 0.5f));
			sPosArray.add(Vector3f(-0.5f, -0.5f, 0.5f));
			sPosArray.add(Vector3f(-0.5f, -0.5f, -0.5f));

			sPosArray.add(Vector3f(-0.5f, 0.5f, -0.5f));
			sPosArray.add(Vector3f(0.5f, 0.5f, -0.5f));
			sPosArray.add(Vector3f(0.5f, 0.5f, 0.5f));
			sPosArray.add(Vector3f(0.5f, 0.5f, 0.5f));
			sPosArray.add(Vector3f(-0.5f, 0.5f, 0.5f));
			sPosArray.add(Vector3f(-0.5f, 0.5f, -0.5f));

			sTexArray.add(Vector2f(0.0f, 0.0f));
			sTexArray.add(Vector2f(1.0f, 0.0f));
			sTexArray.add(Vector2f(1.0f, 1.0f));
			sTexArray.add(Vector2f(1.0f, 1.0f));
			sTexArray.add(Vector2f(0.0f, 1.0f));
			sTexArray.add(Vector2f(0.0f, 0.0f));

			sTexArray.add(Vector2f(0.0f, 0.0f));
			sTexArray.add(Vector2f(1.0f, 0.0f));
			sTexArray.add(Vector2f(1.0f, 1.0f));
			sTexArray.add(Vector2f(1.0f, 1.0f));
			sTexArray.add(Vector2f(0.0f, 1.0f));
			sTexArray.add(Vector2f(0.0f, 0.0f));

			sTexArray.add(Vector2f(1.0f, 0.0f));
			sTexArray.add(Vector2f(1.0f, 1.0f));
			sTexArray.add(Vector2f(0.0f, 1.0f));
			sTexArray.add(Vector2f(0.0f, 1.0f));
			sTexArray.add(Vector2f(0.0f, 0.0f));
			sTexArray.add(Vector2f(1.0f, 0.0f));

			sTexArray.add(Vector2f(1.0f, 0.0f));
			sTexArray.add(Vector2f(1.0f, 1.0f));
			sTexArray.add(Vector2f(0.0f, 1.0f));
			sTexArray.add(Vector2f(0.0f, 1.0f));
			sTexArray.add(Vector2f(0.0f, 0.0f));
			sTexArray.add(Vector2f(1.0f, 0.0f));

			sTexArray.add(Vector2f(0.0f, 1.0f));
			sTexArray.add(Vector2f(1.0f, 1.0f));
			sTexArray.add(Vector2f(1.0f, 0.0f));
			sTexArray.add(Vector2f(1.0f, 0.0f));
			sTexArray.add(Vector2f(0.0f, 0.0f));
			sTexArray.add(Vector2f(0.0f, 1.0f));

			sTexArray.add(Vector2f(0.0f, 1.0f));
			sTexArray.add(Vector2f(1.0f, 1.0f));
			sTexArray.add(Vector2f(1.0f, 0.0f));
			sTexArray.add(Vector2f(1.0f, 0.0f));
			sTexArray.add(Vector2f(0.0f, 0.0f));
			sTexArray.add(Vector2f(0.0f, 1.0f));

			sNormalArray.add(Vector3f(0, 0, -1));
			sNormalArray.add(Vector3f(0, 0, -1));
			sNormalArray.add(Vector3f(0, 0, -1));
			sNormalArray.add(Vector3f(0, 0, -1));
			sNormalArray.add(Vector3f(0, 0, -1));
			sNormalArray.add(Vector3f(0, 0, -1));

			sNormalArray.add(Vector3f(0, 0, 1));
			sNormalArray.add(Vector3f(0, 0, 1));
			sNormalArray.add(Vector3f(0, 0, 1));
			sNormalArray.add(Vector3f(0, 0, 1));
			sNormalArray.add(Vector3f(0, 0, 1));
			sNormalArray.add(Vector3f(0, 0, 1));

			sNormalArray.add(Vector3f(-1, 0, 0));
			sNormalArray.add(Vector3f(-1, 0, 0));
			sNormalArray.add(Vector3f(-1, 0, 0));
			sNormalArray.add(Vector3f(-1, 0, 0));
			sNormalArray.add(Vector3f(-1, 0, 0));
			sNormalArray.add(Vector3f(-1, 0, 0));

			sNormalArray.add(Vector3f(1, 0, 0));
			sNormalArray.add(Vector3f(1, 0, 0));
			sNormalArray.add(Vector3f(1, 0, 0));
			sNormalArray.add(Vector3f(1, 0, 0));
			sNormalArray.add(Vector3f(1, 0, 0));
			sNormalArray.add(Vector3f(1, 0, 0));

			sNormalArray.add(Vector3f(0, -1, 0));
			sNormalArray.add(Vector3f(0, -1, 0));
			sNormalArray.add(Vector3f(0, -1, 0));
			sNormalArray.add(Vector3f(0, -1, 0));
			sNormalArray.add(Vector3f(0, -1, 0));
			sNormalArray.add(Vector3f(0, -1, 0));

			sNormalArray.add(Vector3f(0, 1, 0));
			sNormalArray.add(Vector3f(0, 1, 0));
			sNormalArray.add(Vector3f(0, 1, 0));
			sNormalArray.add(Vector3f(0, 1, 0));
			sNormalArray.add(Vector3f(0, 1, 0));
			sNormalArray.add(Vector3f(0, 1, 0));

			myGeometryInitialized = true;
		}
		setVertex(&sPosArray);
		setTextureCoordinate(&sTexArray);
		setNomral(&sNormalArray);
		addPrimitiveSet(Drawable::TRIANGLES, 0, 36);
	}

	bool Sphere::myGeometryInitialized = false;
	ArrayVec3 Sphere::sPosArray = ArrayVec3();
	ArrayUnsignedInt Sphere::sIndexArray = ArrayUnsignedInt();
	ArrayVec2 Sphere::sTexArray = ArrayVec2();
	ArrayVec3 Sphere::sNormalArray = ArrayVec3();

	Sphere::Sphere()
	{
		if (!myGeometryInitialized)
		{
			GeographicGridTessellation::compute(sPosArray, sIndexArray, sNormalArray, sTexArray, 32, 64,
				1,1,1);
			myGeometryInitialized = true;
		}

		setVertex(&sPosArray);
		setIndex(&sIndexArray);
		setNomral(&sNormalArray);
		setTextureCoordinate(&sTexArray);
	}

	bool Floor::myGeometryInitialized = false;
	ArrayVec3 Floor::sPosArray = ArrayVec3(6);
	ArrayVec2 Floor::sTexArray = ArrayVec2(6);
	ArrayVec3 Floor::sNormalArray = ArrayVec3(6);

	Floor::Floor()
	{
		if (!myGeometryInitialized)
		{
			sPosArray.add(Vector3f(5.0f, -0.5f, 5.0f));
			sPosArray.add(Vector3f(-5.0f, -0.5f, -5.0f));
			sPosArray.add(Vector3f(-5.0f, -0.5f, 5.0f));
			sPosArray.add(Vector3f(5.0f, -0.5f, 5.0f));
			sPosArray.add(Vector3f(5.0f, -0.5f, -5.0f));
			sPosArray.add(Vector3f(-5.0f, -0.5f, -5.0f));

			sTexArray.add(Vector2f(1.0f, 0.0f));
			sTexArray.add(Vector2f(0.0f, 1.0f));
			sTexArray.add(Vector2f(0.0f, 0.0f));
			sTexArray.add(Vector2f(1.0f, 0.0f));
			sTexArray.add(Vector2f(1.0f, 1.0f));
			sTexArray.add(Vector2f(0.0f, 1.0f));

			sNormalArray.add(Vector3f(0, 1, 0));
			sNormalArray.add(Vector3f(0, 1, 0));
			sNormalArray.add(Vector3f(0, 1, 0));
			sNormalArray.add(Vector3f(0, 1, 0));
			sNormalArray.add(Vector3f(0, 1, 0));
			sNormalArray.add(Vector3f(0, 1, 0));

			myGeometryInitialized = true;
		}
		setVertex(&sPosArray);
		setTextureCoordinate(&sTexArray);
		setNomral(&sNormalArray);
		addPrimitiveSet(Drawable::TRIANGLES, 0, 6);
		setBuildTangent(true);
	}

	bool Billboard::myGeometryInitialized = false;
	ArrayVec3 Billboard::sPosArray = ArrayVec3(6);
	ArrayVec2 Billboard::sTexArray = ArrayVec2(6);
	ArrayVec3 Billboard::sNormalArray = ArrayVec3(6);

	Billboard::Billboard()
	{
		if (!myGeometryInitialized)
		{
			sPosArray.add(Vector3f(0.0f, 0.5f, 0.0f));
			sPosArray.add(Vector3f(0.0f, -0.5f, 0.0f));
			sPosArray.add(Vector3f(1.0f, -0.5f, 0.0f));
			sPosArray.add(Vector3f(0.0f, 0.5f, 0.0f));
			sPosArray.add(Vector3f(1.0f, -0.5f, 0.0f));
			sPosArray.add(Vector3f(1.0f, 0.5f, 0.0f));

			sTexArray.add(Vector2f(0.0f, 1.0f));
			sTexArray.add(Vector2f(0.0f, 0.0f));
			sTexArray.add(Vector2f(1.0f, 0.0f));
			sTexArray.add(Vector2f(0.0f, 1.0f));
			sTexArray.add(Vector2f(1.0f, 0.0f));
			sTexArray.add(Vector2f(1.0f, 1.0f));

			sNormalArray.add(Vector3f(0, 0, 1));
			sNormalArray.add(Vector3f(0, 0, 1));
			sNormalArray.add(Vector3f(0, 0, 1));
			sNormalArray.add(Vector3f(0, 0, 1));
			sNormalArray.add(Vector3f(0, 0, 1));
			sNormalArray.add(Vector3f(0, 0, 1));

			myGeometryInitialized = true;
		}
		setVertex(&sPosArray);
		setTextureCoordinate(&sTexArray);
		setNomral(&sNormalArray);
		addPrimitiveSet(Drawable::TRIANGLES, 0, 6);
	}
}
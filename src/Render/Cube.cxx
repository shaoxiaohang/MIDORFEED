#include <Render/Cube.h>

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
			sPosArray[0] = Vector3f(-0.5f, -0.5f, -0.5f);
			sPosArray[1] = Vector3f(0.5f, -0.5f, -0.5f);
			sPosArray[2] = Vector3f(0.5f, 0.5f, -0.5f);
			sPosArray[3] = Vector3f(0.5f, 0.5f, -0.5f);
			sPosArray[4] = Vector3f(-0.5f, 0.5f, -0.5f);
			sPosArray[5] = Vector3f(-0.5f, -0.5f, -0.5f);

			sPosArray[6] = Vector3f(-0.5f, -0.5f, 0.5f);
			sPosArray[7] = Vector3f(0.5f, -0.5f, 0.5f);
			sPosArray[8] = Vector3f(0.5f, 0.5f, 0.5f);
			sPosArray[9] = Vector3f(0.5f, 0.5f, 0.5f);
			sPosArray[10] = Vector3f(-0.5f, 0.5f, 0.5f);
			sPosArray[11] = Vector3f(-0.5f, -0.5f, 0.5f);
	
			sPosArray[12] = Vector3f(-0.5f, 0.5f, 0.5f);
			sPosArray[13] = Vector3f(-0.5f, 0.5f, -0.5f);
			sPosArray[14] = Vector3f(-0.5f, -0.5f, -0.5f);
			sPosArray[15] = Vector3f(-0.5f, -0.5f, -0.5f);
			sPosArray[16] = Vector3f(-0.5f, -0.5f, 0.5f);
			sPosArray[17] = Vector3f(-0.5f, 0.5f, 0.5f);

			sPosArray[18] = Vector3f(0.5f, 0.5f, 0.5f);
			sPosArray[19] = Vector3f(0.5f, 0.5f, -0.5f);
			sPosArray[20] = Vector3f(0.5f, -0.5f, -0.5f);
			sPosArray[21] = Vector3f(0.5f, -0.5f, -0.5f);
			sPosArray[22] = Vector3f(0.5f, -0.5f, 0.5f);
			sPosArray[23] = Vector3f(0.5f, 0.5f, 0.5f);

			sPosArray[24] = Vector3f(-0.5f, -0.5f, -0.5f);
			sPosArray[25] = Vector3f(0.5f, -0.5f, -0.5f);
			sPosArray[26] = Vector3f(0.5f, -0.5f, 0.5f);
			sPosArray[27] = Vector3f(0.5f, -0.5f, 0.5f);
			sPosArray[28] = Vector3f(-0.5f, -0.5f, 0.5f);
			sPosArray[29] = Vector3f(-0.5f, -0.5f, -0.5f);

			sPosArray[30] = Vector3f(-0.5f, 0.5f, -0.5f);
			sPosArray[31] = Vector3f(0.5f, 0.5f, -0.5f);
			sPosArray[32] = Vector3f(0.5f, 0.5f, 0.5f);
			sPosArray[33] = Vector3f(0.5f, 0.5f, 0.5f);
			sPosArray[34] = Vector3f(-0.5f, 0.5f, 0.5f);
			sPosArray[35] = Vector3f(-0.5f, 0.5f, -0.5f);

			sTexArray[0] = Vector2f(0.0f, 0.0f);
			sTexArray[1] = Vector2f(1.0f, 0.0f);
			sTexArray[2] = Vector2f(1.0f, 1.0f);
			sTexArray[3] = Vector2f(1.0f, 1.0f);
			sTexArray[4] = Vector2f(0.0f, 1.0f);
			sTexArray[5] = Vector2f(0.0f, 0.0f);

			sTexArray[6] = Vector2f(0.0f, 0.0f);
			sTexArray[7] = Vector2f(1.0f, 0.0f);
			sTexArray[8] = Vector2f(1.0f, 1.0f);
			sTexArray[9] = Vector2f(1.0f, 1.0f);
			sTexArray[10] = Vector2f(0.0f, 1.0f);
			sTexArray[11] = Vector2f(0.0f, 0.0f);

			sTexArray[12] = Vector2f(1.0f, 0.0f);
			sTexArray[13] = Vector2f(1.0f, 1.0f);
			sTexArray[14] = Vector2f(0.0f, 1.0f);
			sTexArray[15] = Vector2f(0.0f, 1.0f);
			sTexArray[16] = Vector2f(0.0f, 0.0f);
			sTexArray[17] = Vector2f(1.0f, 0.0f);

			sTexArray[18] = Vector2f(1.0f, 0.0f);
			sTexArray[19] = Vector2f(1.0f, 1.0f);
			sTexArray[20] = Vector2f(0.0f, 1.0f);
			sTexArray[21] = Vector2f(0.0f, 1.0f);
			sTexArray[22] = Vector2f(0.0f, 0.0f);
			sTexArray[23] = Vector2f(1.0f, 0.0f);

			sTexArray[24] = Vector2f(0.0f, 1.0f);
			sTexArray[25] = Vector2f(1.0f, 1.0f);
			sTexArray[26] = Vector2f(1.0f, 0.0f);
			sTexArray[27] = Vector2f(1.0f, 0.0f);
			sTexArray[28] = Vector2f(0.0f, 0.0f);
			sTexArray[29] = Vector2f(0.0f, 1.0f);

			sTexArray[30] = Vector2f(0.0f, 1.0f);
			sTexArray[31] = Vector2f(1.0f, 1.0f);
			sTexArray[32] = Vector2f(1.0f, 0.0f);
			sTexArray[33] = Vector2f(1.0f, 0.0f);
			sTexArray[34] = Vector2f(0.0f, 0.0f);
			sTexArray[35] = Vector2f(0.0f, 1.0f);

			sNormalArray[0] = Vector3f(0, 0, -1);
			sNormalArray[1] = Vector3f(0, 0, -1);
			sNormalArray[2] = Vector3f(0, 0, -1);
			sNormalArray[3] = Vector3f(0, 0, -1);
			sNormalArray[4] = Vector3f(0, 0, -1);
			sNormalArray[5] = Vector3f(0, 0, -1);

			sNormalArray[6]  = Vector3f(0, 0, 1);
			sNormalArray[7]  = Vector3f(0, 0, 1);
			sNormalArray[8]  = Vector3f(0, 0, 1);
			sNormalArray[9]  = Vector3f(0, 0, 1);
			sNormalArray[10] = Vector3f(0, 0, 1);
			sNormalArray[11] = Vector3f(0, 0, 1);

			sNormalArray[12] = Vector3f(-1, 0, 0);
			sNormalArray[13] = Vector3f(-1, 0, 0);
			sNormalArray[14] = Vector3f(-1, 0, 0);
			sNormalArray[15] = Vector3f(-1, 0, 0);
			sNormalArray[16] = Vector3f(-1, 0, 0);
			sNormalArray[17] = Vector3f(-1, 0, 0);

			sNormalArray[18] = Vector3f(1, 0, 0);
			sNormalArray[19] = Vector3f(1, 0, 0);
			sNormalArray[20] = Vector3f(1, 0, 0);
			sNormalArray[21] = Vector3f(1, 0, 0);
			sNormalArray[22] = Vector3f(1, 0, 0);
			sNormalArray[23] = Vector3f(1, 0, 0);

			sNormalArray[24] = Vector3f(0, -1, 0);
			sNormalArray[25] = Vector3f(0, -1, 0);
			sNormalArray[26] = Vector3f(0, -1, 0);
			sNormalArray[27] = Vector3f(0, -1, 0);
			sNormalArray[28] = Vector3f(0, -1, 0);
			sNormalArray[29] = Vector3f(0, -1, 0);

			sNormalArray[30] = Vector3f(0, 1, 0);
			sNormalArray[31] = Vector3f(0, 1, 0);
			sNormalArray[32] = Vector3f(0, 1, 0);
			sNormalArray[33] = Vector3f(0, 1, 0);
			sNormalArray[34] = Vector3f(0, 1, 0);
			sNormalArray[35] = Vector3f(0, 1, 0);

			myGeometryInitialized = true;
		}
		setVertex(&sPosArray);
		setTextureCoordinate(&sTexArray);
		setNomral(&sNormalArray);
		addPrimitiveSet(Drawable::TRIANGLES, 0, 36);
	}

	bool Floor::myGeometryInitialized = false;
	ArrayVec3 Floor::sPosArray = ArrayVec3(6);
	ArrayVec2 Floor::sTexArray = ArrayVec2(6);
	ArrayVec3 Floor::sNormalArray = ArrayVec3(6);

	Floor::Floor()
	{
		if (!myGeometryInitialized)
		{
			sPosArray[0] = Vector3f(5.0f, -0.5f, 5.0f);
			sPosArray[1] = Vector3f(-5.0f, -0.5f, 5.0f);
			sPosArray[2] = Vector3f(-5.0f, -0.5f, -5.0f);
			sPosArray[3] = Vector3f(5.0f, -0.5f, 5.0f);
			sPosArray[4] = Vector3f(-5.0f, -0.5f, -5.0f);
			sPosArray[5] = Vector3f(5.0f, -0.5f, -5.0f);

			sTexArray[0] = Vector2f(2.0f, 0.0f);
			sTexArray[1] = Vector2f(0.0f, 0.0f);
			sTexArray[2] = Vector2f(0.0f, 2.0f);
			sTexArray[3] = Vector2f(2.0f, 0.0f);
			sTexArray[4] = Vector2f(0.0f, 2.0f);
			sTexArray[5] = Vector2f(2.0f, 2.0f);

			sNormalArray[0] = Vector3f(0, 1, 0);
			sNormalArray[1] = Vector3f(0, 1, 0);
			sNormalArray[2] = Vector3f(0, 1, 0);
			sNormalArray[3] = Vector3f(0, 1, 0);
			sNormalArray[4] = Vector3f(0, 1, 0);
			sNormalArray[5] = Vector3f(0, 1, 0);

			myGeometryInitialized = true;
		}
		setVertex(&sPosArray);
		setTextureCoordinate(&sTexArray);
		setNomral(&sNormalArray);
		addPrimitiveSet(Drawable::TRIANGLES, 0, 6);
	}

	bool Billboard::myGeometryInitialized = false;
	ArrayVec3 Billboard::sPosArray = ArrayVec3(6);
	ArrayVec2 Billboard::sTexArray = ArrayVec2(6);
	ArrayVec3 Billboard::sNormalArray = ArrayVec3(6);

	Billboard::Billboard()
	{
		if (!myGeometryInitialized)
		{
			sPosArray[0] = Vector3f(0.0f, 0.5f, 0.0f);
			sPosArray[1] = Vector3f(0.0f, -0.5f, 0.0f);
			sPosArray[2] = Vector3f(1.0f, -0.5f, 0.0f);
			sPosArray[3] = Vector3f(0.0f, 0.5f, 0.0f);
			sPosArray[4] = Vector3f(1.0f, -0.5f, 0.0f);
			sPosArray[5] = Vector3f(1.0f, 0.5f, 0.0f);

			sTexArray[0] = Vector2f(0.0f, 1.0f);
			sTexArray[1] = Vector2f(0.0f, 0.0f);
			sTexArray[2] = Vector2f(1.0f, 0.0f);
			sTexArray[3] = Vector2f(0.0f, 1.0f);
			sTexArray[4] = Vector2f(1.0f, 0.0f);
			sTexArray[5] = Vector2f(1.0f, 1.0f);

			sNormalArray[0] = Vector3f(0, 0, 1);
			sNormalArray[1] = Vector3f(0, 0, 1);
			sNormalArray[2] = Vector3f(0, 0, 1);
			sNormalArray[3] = Vector3f(0, 0, 1);
			sNormalArray[4] = Vector3f(0, 0, 1);
			sNormalArray[5] = Vector3f(0, 0, 1);

			myGeometryInitialized = true;
		}
		setVertex(&sPosArray);
		setTextureCoordinate(&sTexArray);
		setNomral(&sNormalArray);
		addPrimitiveSet(Drawable::TRIANGLES, 0, 6);
	}
}
#include <Render/Cube.h>

namespace vrv
{
	bool Cube::myGeometryInitialized = false;
	ArrayVec3 Cube::sPosArray = ArrayVec3(3);
	ArrayVec2 Cube::sTexArray = ArrayVec2(3);

	Cube::Cube()
	{
		if (!myGeometryInitialized)
		{
			sPosArray[0]  = Vector3f(-0.5f, -0.5f, -0.5f);
			sPosArray[1]  = Vector3f(0.5f, -0.5f, -0.5f);
			sPosArray[2]  = Vector3f(0.5f, 0.5f, -0.5f);
			/*sPosArray[3]  = Vector3f(0.5f, 0.5f, -0.5f);
			sPosArray[4]  = Vector3f(-0.5f, 0.5f, -0.5f);
			sPosArray[5]  = Vector3f(-0.5f, -0.5f, -0.5f);

			sPosArray[6]  = Vector3f(-0.5f, -0.5f, 0.5f);
			sPosArray[7]  = Vector3f(0.5f, -0.5f, 0.5f);
			sPosArray[8]  = Vector3f(0.5f, 0.5f, 0.5f);
			sPosArray[9]  = Vector3f(0.5f, 0.5f, 0.5f);
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
			sPosArray[35] = Vector3f(-0.5f, 0.5f, -0.5f);*/

			sTexArray[0] = Vector2f(0.0f, 0.0f);
			sTexArray[1] = Vector2f(1.0f, 0.0f);
			sTexArray[2] = Vector2f(1.0f, 1.0f);
			/*sTexArray[3] = Vector2f(1.0f, 1.0f);
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
			sTexArray[35] = Vector2f(0.0f, 1.0f);*/

			myGeometryInitialized = true;
		}
		setVertex(&sPosArray);
		setTextureCoordinate(&sTexArray);
		addPrimitiveSet(Drawable::TRIANGLES, 0, 3);
	}
}
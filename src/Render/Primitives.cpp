#include <Render/Primitives.h>
#include <Render/Tessellation.h>
namespace vrv
{
  bool Cube::myGeometryInitialized = false;
  ArrayVec3 Cube::sPosArray;
  ArrayVec2 Cube::sTexArray;
  ArrayVec3 Cube::sNormalArray;

  Cube::Cube()
  {
    if (!myGeometryInitialized)
    {
      sPosArray.add(Vector3f(-0.5f, -0.5f, -0.5f));
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
    addVertexAttribute(0, &sPosArray);
    addVertexAttribute(1, &sTexArray);
    addVertexAttribute(2, &sNormalArray);
    addPrimitiveSet(Drawable::TRIANGLES, 0, 36);
  }

  bool Sphere::myGeometryInitialized = false;
  ArrayVec3 Sphere::sPosArray;
  ArrayUnsignedInt Sphere::sIndexArray;
  ArrayVec2 Sphere::sTexArray;
  ArrayVec3 Sphere::sNormalArray;

  Sphere::Sphere()
  {
    if (!myGeometryInitialized)
    {
      GeographicGridTessellation::compute(sPosArray, sIndexArray, sNormalArray, sTexArray, 32, 64,
        1, 1, 1);
      myGeometryInitialized = true;
    }

    addVertexIndex(&sIndexArray);
    addVertexAttribute(0, &sPosArray);
    addVertexAttribute(1, &sTexArray);
    addVertexAttribute(2, &sNormalArray);
  }

  bool Floor::myGeometryInitialized = false;
  ArrayVec3 Floor::sPosArray;
  ArrayVec2 Floor::sTexArray;
  ArrayVec3 Floor::sNormalArray;

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
    addVertexAttribute(0, &sPosArray);
    addVertexAttribute(1, &sTexArray);
    addVertexAttribute(2, &sNormalArray);
    addPrimitiveSet(Drawable::TRIANGLES, 0, 6);
  }

  bool Billboard::myGeometryInitialized = false;
  ArrayVec3 Billboard::sPosArray;
  ArrayVec2 Billboard::sTexArray;
  ArrayVec3 Billboard::sNormalArray;

  Billboard::Billboard()
  {
    if (!myGeometryInitialized)
    {
      sPosArray.add(Vector3f(-0.5f, 0.5f, 0.0f));
      sPosArray.add(Vector3f(-0.5f, -0.5f, 0.0f));
      sPosArray.add(Vector3f(0.5f, -0.5f, 0.0f));
      sPosArray.add(Vector3f(-0.5f, 0.5f, 0.0f));
      sPosArray.add(Vector3f(0.5f, -0.5f, 0.0f));
      sPosArray.add(Vector3f(0.5f, 0.5f, 0.0f));

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
    addVertexAttribute(0, &sPosArray);
    addVertexAttribute(1, &sTexArray);
    addVertexAttribute(2, &sNormalArray);
    addPrimitiveSet(Drawable::TRIANGLES, 0, 6);
  }
}
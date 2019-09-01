#include <Render/Viewer.h>
#include <Render/Node.h>
#include <Render/Array.h>
#include <Render/Primitives.h>
#include <Render/Texture.h>
#include <Core/Matrix4f.h>
#include <Core/Matrix3f.h>
#include <Core/Vector3f.h>
#include <Core/Vector4f.h>
#include <Render/Camera.h>
#include <Render/Light.h>
#include <Render/Scene.h>
#include <Render/Material.h>
#include <Render/Model.h>
#include <Render/Scenario.h>
#include <Render/Geometry.h>
#include <Render/RenderState.h>
#include <Render/DrawState.h>
#include <Render/Scene.h>
#include <Render/Map.h>
#include <Render/Ellipsoid.h>

using namespace vrv;
int main(int argc, char** argv)
{
	Viewer* viewer = new Viewer(argc,argv);
	viewer->initialize(800, 600, "main window");

	Scenario* test = new Scenario("model.scene");
	viewer->setSceneData(test);
   viewer->masterCamera()->focousOnTarget(Vector3f(0, 0, 0), 1.0);
	viewer->run();
	
	return 0;
}
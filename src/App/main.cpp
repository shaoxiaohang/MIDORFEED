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
#include <Render/Scene.h>
#include <Render/Map.h>
#include <Render/Ellipsoid.h>
#include <GUI/Button.h>
#include <GUI/Label.h>

using namespace vrv;
int main(int argc, char** argv)
{
	Viewer* viewer = new Viewer(argc,argv);
	viewer->initialize(800, 600, "main window");

	//Scenario* test = new Scenario("simple.scene");
   Label* label = new Label(0);
   label->setText("H");
	//viewer->setSceneData(0);
   //viewer->masterCamera()->focousOnTarget(viewer->scene()->root());
	viewer->run();
	
	return 0;
}
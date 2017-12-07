#include <Render/Viewer.h>
#include <Core/Node.h>
#include <Render/Array.h>
#include <Render/Primitives.h>
#include <Render/Texture.h>
#include <Core/Matrix4.h>
#include <Core/Matrix3.h>
#include <Core/Vector3.h>
#include <Core/Vector4.h>
#include <Render/Camera.h>
#include <Render/Light.h>
#include <Render/Scene.h>
#include <Render/Material.h>
#include <Render/Model.h>
#include <Render/Scenario.h>
#include <Render/Geometry.h>
#include <Render/RenderState.h>
#include <Render/DrawState.h>
#include <Render/ShaderManager.h>
using namespace vrv;
int main(int argc, char** argv)
{
	Viewer* viewer = new Viewer(argc,argv);
	viewer->initialize(800, 600, "main window");

	Scenario* test = new Scenario("DepthTest.scene");
	viewer->setSceneData(test);

	//Geometry* points = new Geometry();

	//ArrayVec2 pos;
	//pos.add(Vector2f(-0.5, 0.5));
	//pos.add(Vector2f(0.5, 0.5));
	//pos.add(Vector2f(-0.5, -0.5));
	//pos.add(Vector2f(0.5, -0.5));
	//points->setVertex(&pos);

	//points->addPrimitiveSet(Drawable::POINTS, 0, 4);
	//points->buildGeometry();
	//points->drawState()->setProgram(ShaderManager::instance().getProgram(ShaderManager::GeometryTestShader));

	//Node* root = new Node();
	//root->addDrawable(points);
	//viewer->setSceneData(root);


	viewer->masterCamera()->setProjectionMatrixAsPerspective(45.0f,800.0f/600.0f,0.1f,100.0f);

	

	viewer->run();
	
	return 0;
}
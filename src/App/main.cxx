#include<Render/Viewer.h>
#include<Core/Node.h>
#include<Render/Array.h>
#include<Render/Cube.h>
#include<Render/Texture2D.h>
#include<Core/Matrix4.h>
#include<Core/Matrix3.h>
#include<Core/Vector3.h>
#include<Core/Vector4.h>
#include<Render/Camera.h>
using namespace vrv;
int main(int argc, char** argv)
{
	Viewer* viewer = new Viewer(argc,argv);
	viewer->initialize(800, 600, "main window");

	Node* node = new Node("root");
	Cube* cube = new Cube();
	Texture2D* texture = new Texture2D("../data/image/wall.jpg");
	cube->setTexture2D(texture, 0);
	node->addDrawable(cube);
	node->setColor(Vector4f(1, 0, 0, 1));
	node->setPosition(Vector3f(1, 0, 0));

	viewer->setSceneData(node);
	viewer->masterCamera()->setProjectionMatrixAsPerspective(45.0f,800.0f/600.0f,0.1f,100.0f);

	viewer->run();
	
	return 0;
}
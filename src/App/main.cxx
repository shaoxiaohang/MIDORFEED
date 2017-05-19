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

	viewer->setSceneData(node);
	viewer->masterCamera()->setProjectionMatrixAsPerspective(0,800,0,600,0.1f,100.0f);

	Matrix4f pro = viewer->masterCamera()->getViewMatrix();
	Vector4f pos1 = pro*Vector3f(-0.5f, -0.5f, -0.5f);
	Vector4f pos2 = pro*Vector3f(0.5f, -0.5f, -0.5f);
	Vector4f pos3 = pro*Vector3f(0.5f, 0.5f, -0.5f);

	viewer->run();
	
	return 0;
}
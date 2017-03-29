#include<Render/Viewer.h>
#include<Core/Node.h>
#include<Render/Array.h>
#include<Render/Geometry.h>
#include<Render/Texture2D.h>
#include<Core/Matrix4.h>
#include<Core/Vector3.h>
#include<Core/Vector4.h>
using namespace vrv;
int main(int argc, char** argv)
{
	Viewer* viewer = new Viewer(argc,argv);
	viewer->initialize(800, 600, "main window");

	Node* node = new Node("root");
	Geometry* triangle = new Geometry();
	ArrayVec3 pos(4);
	pos[0] = Vector3f(-0.5, -0.5, 0);
	pos[1] = Vector3f(0.5, -0.5, 0);
	pos[2] = Vector3f(0.5, 0.5, 0);
	pos[3] = Vector3f(-0.5, 0.5, 0);
	ArrayVec2 st(4);
	st[0] = Vector2f(0, 0);
	st[1] = Vector2f(1, 0);
	st[2] = Vector2f(1, 1);
	st[3] = Vector2f(0, 1);
	triangle->setVertex(&pos);
	triangle->addPrimitiveSet(Drawable::QUADS, 0, 4);
	triangle->setTextureCoordinate(&st);
	Texture2D* texture = new Texture2D("../data/image/wall.jpg");
	triangle->setTexture2D(texture, 0);
	node->addDrawable(triangle);

	viewer->setSceneData(node);
	viewer->run();
	
	return 0;
}
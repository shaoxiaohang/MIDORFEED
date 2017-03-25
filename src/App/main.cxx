#include<Render/Viewer.h>
#include<Core/Node.h>
#include<Render/Array.h>
#include<Render/Geometry.h>
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
	ArrayUnsignedInt index(3);
	index[0] = 0;
	index[1] = 2;
	index[2] = 3;
	triangle->setVertexArray(&pos);
	triangle->addPrimitiveSet(Drawable::TRIANGLES, 0, 3);
	triangle->addPrimitiveSet(Drawable::TRIANGLES, 3, index.dataType());
	triangle->setIndexArray(&index);
	node->addDrawable(triangle);

	viewer->setSceneData(node);
	viewer->run();
	
	return 0;
}
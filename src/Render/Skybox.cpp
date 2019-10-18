#include <Render/Skybox.h>
#include <Render/Geometry.h>
#include <Render/Texture3D.h>
#include <Render/RenderState.h>
#include <Render/StateSet.h>
#include <Render/Program.h>

namespace vrv
{
	Skybox::Skybox(const std::vector<std::string>& fileName)
		: myFileNames(fileName)
	{
		initialize();
	}

	void Skybox::initialize()
	{
		myCubeMap = new Texture3D(myFileNames);
		RenderState* renderState = new RenderState();
		renderState->depthTest().setDepthTestFunction(DepthTest::DEPTH_FUNC_LEQUAL);
		myCube = new Geometry();

      myStateSet = new StateSet(renderState, new Program("../data/shader/skybox.vert",
			"../data/shader/skybox.frag"));

		ArrayVec3* vertex = new ArrayVec3();
		vertex->add(Vector3f(-1,1,-1));
		vertex->add(Vector3f(-1,-1,-1));
		vertex->add(Vector3f(1,-1,-1));
		vertex->add(Vector3f(1,-1,-1));
		vertex->add(Vector3f(1,1,-1));
		vertex->add(Vector3f(-1,1,-1));

		vertex->add(Vector3f(-1,-1,1));
		vertex->add(Vector3f(-1,-1,-1));
		vertex->add(Vector3f(-1,1,-1));
		vertex->add(Vector3f(-1,1,-1));
		vertex->add(Vector3f(-1,1,1));
		vertex->add(Vector3f(-1,-1,1));

		vertex->add(Vector3f(1,-1,-1));
		vertex->add(Vector3f(1,-1,1));
		vertex->add(Vector3f(1,1,1));
		vertex->add(Vector3f(1,1,1));
		vertex->add(Vector3f(1,1,-1));
		vertex->add(Vector3f(1,-1,-1));

		vertex->add(Vector3f(-1,-1,1));
		vertex->add(Vector3f(-1,1,1));
		vertex->add(Vector3f(1,1,1));
		vertex->add(Vector3f(1,1,1));
		vertex->add(Vector3f(1,-1,1));
		vertex->add(Vector3f(-1,-1,1));

		vertex->add(Vector3f(-1,1,-1));
		vertex->add(Vector3f(1,1,-1));
		vertex->add(Vector3f(1,1,1));
		vertex->add(Vector3f(1,1,1));
		vertex->add(Vector3f(-1,1,1));
		vertex->add(Vector3f(-1,1,-1));

		vertex->add(Vector3f(-1,-1,-1));
		vertex->add(Vector3f(-1,-1,1));
		vertex->add(Vector3f(1,-1,-1));
		vertex->add(Vector3f(1,-1,-1));
		vertex->add(Vector3f(-1,-1,1));
		vertex->add(Vector3f(1,-1,1));
		
		myCube->addVertexAttribute(0, vertex);
		myCube->addPrimitiveSet(Drawable::TRIANGLES, 0, 36);
	}

	void Skybox::draw()
	{
      myStateSet->program()->set("skybox", 0);
		myCubeMap->bindToPoint(0);
		myCube->drawImplementation();
	}

	Texture3D* Skybox::cubeMap()
	{
		return myCubeMap;
	}
}
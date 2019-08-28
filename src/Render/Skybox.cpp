#include <Render/Skybox.h>
#include <Render/Geometry.h>
#include <Render/Texture3D.h>
#include <Render/RenderState.h>
#include <Render/DrawState.h>
#include <Render/Program.h>

#ifdef DrawState
#undef DrawState
#endif

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

		myDrawState = new DrawState(renderState, new Program("../data/shader/skybox.vert",
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
		
		myCube->setVertex(vertex);
		myCube->addPrimitiveSet(Drawable::TRIANGLES, 0, 36);
		myCube->buildGeometry();
	}

	void Skybox::draw()
	{
		myDrawState->program()->set("skybox", 0);
		myCubeMap->bindToPoint(0);
		myCube->drawImplementation(myDrawState);
	}

	Texture3D* Skybox::cubeMap()
	{
		return myCubeMap;
	}
}
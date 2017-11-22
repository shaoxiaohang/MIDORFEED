#include <Render/ProgramFactory.h>
#include <Render/Program.h>
#include <Render/ShaderManager.h>
namespace vrv
{
	ProgramFactory::ProgramFactory(int type)
		: myType(type)
	{

	}

	int ProgramFactory::type()
	{
		return myType;
	}

	PhoneLightingProgramFactory::PhoneLightingProgramFactory()
		: ProgramFactory(ShaderManager::PhoneLighting)
	{}

	Program* PhoneLightingProgramFactory::createProgram()
	{
		Program* program = new Program("../data/shader/phoneLighting.vert", "../data/shader/phoneLighting.frag");
		program->link();
		return program;
	}


	VisualizeDepthBufferProgramFactory::VisualizeDepthBufferProgramFactory()
		: ProgramFactory(ShaderManager::VisualizeDepthBuffer)
	{}

	Program* VisualizeDepthBufferProgramFactory::createProgram()
	{
		Program* program = new Program("../data/shader/visualizeDepthBuffer.vert", "../data/shader/visualizeDepthBuffer.frag");
		program->link();
		return program;
	}

	OutlineObjectsProgramFactory::OutlineObjectsProgramFactory()
		: ProgramFactory(ShaderManager::OutLineObject)
	{}

	Program* OutlineObjectsProgramFactory::createProgram()
	{
		Program* program = new Program("../data/shader/outlineObject.vert", "../data/shader/outlineObject.frag");
		program->link();
		return program;
	}

	DefaultQuadProgramFactory::DefaultQuadProgramFactory()
		: ProgramFactory(ShaderManager::DefaultQuadShader)
	{}

	Program* DefaultQuadProgramFactory::createProgram()
	{
		Program* program = new Program("../data/shader/defaultQuad.vert", "../data/shader/defaultQuad.frag");
		program->link();
		return program;
	}

	ConfigurablePostEffectProgramFactory::ConfigurablePostEffectProgramFactory()
		: ProgramFactory(ShaderManager::ConfigurablePostEffectShader)
	{}

	Program* ConfigurablePostEffectProgramFactory::createProgram()
	{
		Program* program = new Program("../data/shader/configurablePostEffect.vert", 
			"../data/shader/configurablePostEffect.frag");
		program->link();
		return program;
	}

	SkyBoxProgramFactory::SkyBoxProgramFactory()
		: ProgramFactory(ShaderManager::SkyBoxShader)
	{}

	Program* SkyBoxProgramFactory::createProgram()
	{
		Program* program = new Program("../data/shader/skybox.vert",
			"../data/shader/skybox.frag");
		program->link();
		return program;
	}

	GeometryTestProgramFactory::GeometryTestProgramFactory()
		:ProgramFactory(ShaderManager::GeometryTestShader)
	{}

	Program* GeometryTestProgramFactory::createProgram()
	{
		Program* program = new Program("../data/shader/geometryTest.vert",
			"../data/shader/geometryTest.frag", "../data/shader/geometryTest.geom");
		program->link();
		return program;
	}
}
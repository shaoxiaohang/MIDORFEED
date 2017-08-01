#include <Render/ProgramFactory.h>
#include <Render/Program.h>
namespace vrv
{
	ProgramFactory::ProgramFactory(const std::string& name)
		: myName(name)
	{

	}

	const std::string ProgramFactory::name()
	{
		return myName;
	}

	PhoneLightingProgramFactory::PhoneLightingProgramFactory()
		: ProgramFactory("phoneLighting")
	{}

	Program* PhoneLightingProgramFactory::createProgram()
	{
		Program* program = new Program("../data/shader/phoneLighting.vert", "../data/shader/phoneLighting.frag");
		program->link();
		return program;
	}


	VisualizeDepthBufferProgramFactory::VisualizeDepthBufferProgramFactory()
		: ProgramFactory("visualize_depth_buffer")
	{}

	Program* VisualizeDepthBufferProgramFactory::createProgram()
	{
		Program* program = new Program("../data/shader/visualizeDepthBuffer.vert", "../data/shader/visualizeDepthBuffer.frag");
		program->link();
		return program;
	}

	OutlineObjectsProgramFactory::OutlineObjectsProgramFactory()
		: ProgramFactory("noLighting")
	{}

	Program* OutlineObjectsProgramFactory::createProgram()
	{
		Program* program = new Program("../data/shader/noLighting.vert", "../data/shader/noLighting.frag");
		program->link();
		return program;
	}
}
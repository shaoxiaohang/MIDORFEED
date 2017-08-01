#include <Render/ShaderManager.h>
#include <Render/ProgramFactory.h>
namespace vrv
{
	ShaderManager* ShaderManager::myInstance = 0;

	ShaderManager::ShaderManager()
	{
		PhoneLightingProgramFactory* phoneLighting = new PhoneLightingProgramFactory();
		VisualizeDepthBufferProgramFactory* visualDepth = new VisualizeDepthBufferProgramFactory();
		OutlineObjectsProgramFactory* outlineObjects = new OutlineObjectsProgramFactory();
		myProgramFactories.push_back(phoneLighting);
		myProgramFactories.push_back(visualDepth);
		myProgramFactories.push_back(outlineObjects);
		createShaders();
	}

	void ShaderManager::createShaders()
	{
		ProgramFactoryList::iterator itor = myProgramFactories.begin();
		for (; itor != myProgramFactories.end(); ++itor)
		{
			myProgramsMap.insert(std::make_pair((*itor)->name(), (*itor)->createProgram()));
		}
	}

	Program* ShaderManager::getProgram(ShaderName name)
	{
		std::string shaderName;
		switch (name)
		{
		case vrv::ShaderManager::NoLighting:
			shaderName = "noLighting";
			break;
		case vrv::ShaderManager::PhoneLighting:
			shaderName= "phoneLighting";
			break;
		case vrv::ShaderManager::VisualizeDepthBuffer:
			shaderName = "visualize_depth_buffer";
			break;
		default:
			break;
		}

		if (myProgramsMap.find(shaderName) != myProgramsMap.end())
		{
			return myProgramsMap[shaderName];
		}

		return 0;
	}
}
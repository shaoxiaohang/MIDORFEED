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
		DefaultQuadProgramFactory* defaultQuadShader = new DefaultQuadProgramFactory();
		ConfigurablePostEffectProgramFactory* configurablePostEffect = new ConfigurablePostEffectProgramFactory();
		myProgramFactories.push_back(phoneLighting);
		myProgramFactories.push_back(visualDepth);
		myProgramFactories.push_back(outlineObjects);
		myProgramFactories.push_back(defaultQuadShader);
		myProgramFactories.push_back(configurablePostEffect);
		createShaders();
	}

	void ShaderManager::createShaders()
	{
		ProgramFactoryList::iterator itor = myProgramFactories.begin();
		for (; itor != myProgramFactories.end(); ++itor)
		{
			myProgramsMap.insert(std::make_pair((*itor)->type(), (*itor)->createProgram()));
		}
	}

	Program* ShaderManager::getProgram(ShaderType type)
	{
		if (myProgramsMap.find(type) != myProgramsMap.end())
		{
			return myProgramsMap[type];
		}

		return 0;
	}
}
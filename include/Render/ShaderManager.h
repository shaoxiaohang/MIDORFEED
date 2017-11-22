#pragma once
#include <Core/Singleton.h>
#include <map>
#include <vector>
#include <string>
namespace vrv
{
	class Program;
	class ProgramFactory;
	class ShaderManager : public Singleton<ShaderManager>
	{
	public:
		enum ShaderType
		{
			PhoneLighting,
			VisualizeDepthBuffer,
			OutLineObject,
			DefaultQuadShader,
			ConfigurablePostEffectShader,
			SkyBoxShader,
			GeometryTestShader
		};
		typedef std::vector<ProgramFactory*> ProgramFactoryList;
		typedef std::map<int, Program*> ProgramMap;
	public:
		ShaderManager();
		Program* getProgram(ShaderType type);
	protected:
		void createShaders();
	protected:
		ProgramFactoryList myProgramFactories;
		ProgramMap myProgramsMap;
	};
}
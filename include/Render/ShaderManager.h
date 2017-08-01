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
		typedef std::vector<ProgramFactory*> ProgramFactoryList;
		typedef std::map<std::string, Program*> ProgramMap;
		enum ShaderName
		{
			NoLighting,
			PhoneLighting,
			VisualizeDepthBuffer
		};
	public:
		ShaderManager();
		Program* getProgram(ShaderName name);
	protected:
		void createShaders();
	protected:
		ProgramFactoryList myProgramFactories;
		ProgramMap myProgramsMap;
	};
}
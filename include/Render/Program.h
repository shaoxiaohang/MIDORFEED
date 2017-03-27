#pragma once
#include<string>
#include<vector>
#include<map>
#include<Render/Uniform.h>
namespace vrv
{
	class Shader;
	class Program
	{
	public:
		typedef std::map<std::string, Uniform*> UniformMap;
		typedef std::map<std::string, AutomaticUniform*> AutomaticUniformMap;
		typedef std::map<std::string, AutomaticUniformFactory*> AutomaticUniformFactoryMap;
	public:
		Program(const std::string& vertFile, const std::string& fragFile);
		Program(const Shader* vert, const Shader* frag);
		~Program();
		bool operator< (const Program& pro);
		bool operator> (const Program& pro);

		Shader* vertexShader();
		Shader* fragmentShader();
		void link();
		static bool checkProgramLinkStatus(unsigned int id,std::string& error);
		static Uniform* createUniform(std::string name, Uniform::UniformType type);
		Uniform* getUniform(std::string name);
		void updateUniforms();
		void use();
		void unuse();
	protected:
		void populateUniforms();
		void populateAutomaticUniforms();
		void clearUniforms();
		static void registerAutomaticUniformFactories();
	protected:
		unsigned int myID;
		Shader* myVertShader;
		Shader* myFragShader;
		UniformMap myUniformsMap;
		AutomaticUniformMap myAutomaticUniformsMap;
		static bool myAutomaticUniformsFactoryInitialized;
		static AutomaticUniformFactoryMap myAutomaticUniformFactories;
	};
}
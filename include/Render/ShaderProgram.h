#pragma once
#include<string>
#include<vector>
#include<map>
#include<Render/ShaderUniform.h>
namespace vrv
{
	class Shader;
	class ShaderProgram
	{
	public:
		typedef std::map<std::string, ShaderUniform*> UniformMap;
		typedef std::map<std::string, AutomaticUniform*> AutomaticUniformMap;
		typedef std::map<std::string, AutomaticUniformFactory*> AutomaticUniformFactoryMap;
	public:
		ShaderProgram(const std::string& vertFile, const std::string& fragFile);
		ShaderProgram(const Shader* vert, const Shader* frag);
		~ShaderProgram();
		bool operator< (const ShaderProgram& pro);
		bool operator> (const ShaderProgram& pro);

		Shader* vertexShader();
		Shader* fragmentShader();
		void link();
		static bool checkProgramLinkStatus(unsigned int id,std::string& error);
		static ShaderUniform* createUniform(std::string name, ShaderUniform::UniformType type);
		void updateUniforms();
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
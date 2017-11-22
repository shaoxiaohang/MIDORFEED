#pragma once
#include <string>
#include <vector>
#include <map>
#include <Render/Uniform.h>
#include <Render/UniformBufferObject.h>
namespace vrv
{
	class Shader;
	class Scene;
	class Program
	{
	public:
		typedef std::map<std::string, Uniform*> UniformMap;
		typedef std::map<std::string, AutomaticUniform*> AutomaticUniformMap;
		typedef std::map<std::string, AutomaticUniformFactory*> AutomaticUniformFactoryMap;
	public:
		Program(const std::string& vertFile, const std::string& fragFile, std::string geometry = "");
		Program(const Shader* vert, const Shader* frag);
		~Program();
		bool operator< (const Program& pro);

		Shader* vertexShader() const;
		Shader* fragmentShader() const;
		void link();
		static bool checkProgramLinkStatus(unsigned int id,std::string& error);
		static Uniform* createUniform(std::string name, Uniform::UniformType type, int location);
		Uniform* getUniform(std::string name);
		void updateUniforms();
		void use();
		void unuse();
		void bindUniformBufferToPoint(const std::string& uniformBuffer, int point);
	protected:
		void populateUniforms();
		void clearUniforms();
		static void registerAutomaticUniformFactories();
		static void setUpUniformBufferObject();
	protected:
		unsigned int myID;
		Shader* myVertShader;
		Shader* myFragShader;
		Shader* myGeometryShader;
		UniformMap myUniformsMap;
		static bool myAutomaticUniformsFactoryInitialized;
		static AutomaticUniformFactoryMap myAutomaticUniformFactories;
		static bool myUniformBufferObjectInitialized;
		static UniformBufferObject* myUniformBufferObject;
	};
}
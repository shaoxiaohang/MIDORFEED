#pragma once
#include<string>
namespace vrv
{
	class Shader;
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& vertFile, const std::string& fragFile);
		ShaderProgram(const Shader* vert, const Shader* frag);
		~ShaderProgram();
		bool operator< (const ShaderProgram& pro);
		bool operator> (const ShaderProgram& pro);

		Shader* vertexShader();
		Shader* fragmentShader();
		static bool checkProgramLinkStatus(unsigned int id,std::string& error);
		void link();
	protected:
		unsigned int myID;
		Shader* myVertShader;
		Shader* myFragShader;
	};
}
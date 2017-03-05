#pragma once
#include <string>
#include <map>
namespace vrv
{
	class Shader
	{
	public:
		typedef std::map<const std::string, float> ConstantsMap;
		enum ShaderType
		{
			VertexShader,
			FragmentShader
		};

		Shader(ShaderType type,const std::string& fileName);
		unsigned int createShader();
		static bool checkCompileStatus(unsigned int id);
		static void addShaderUniformConstant(const std::string& name, float value);

	protected:
		unsigned int toGLEnum();

	protected:
		ShaderType myType;
		std::string mySource;
		static bool myInitialized;
		static ConstantsMap myConstansMap;
	};
}
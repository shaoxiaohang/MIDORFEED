#pragma once
#include <string>
#include <map>
#include <typeinfo>
#include <Core/Vector3.h>
#include <Core/Vector4.h>
namespace vrv
{
	class ShaderAttribute
	{
	public:
		ShaderAttribute(std::string name, unsigned int location);
		unsigned int location();
		const std::string& name();
		virtual std::string typeToString() = 0;
	protected:
		std::string myName;
		unsigned int myLocation;
	};

	class ShaderAttributeInt : public ShaderAttribute
	{
	public:
		ShaderAttributeInt(std::string name, unsigned int location);
		std::string typeToString();
	};

	class ShaderAttributefloat : public ShaderAttribute
	{
	public:
		ShaderAttributefloat(std::string name, unsigned int location);
		std::string typeToString();
	};

	class ShaderAttributeVector3f : public ShaderAttribute
	{
	public:
		ShaderAttributeVector3f(std::string name, unsigned int location);
		std::string typeToString();
	};

	class ShaderAttributeVector4f : public ShaderAttribute
	{
	public:
		ShaderAttributeVector4f(std::string name, unsigned int location);
		std::string typeToString();
	};

	class Shader
	{
	public:
		typedef std::map<const std::string, float> ConstantsMap;
		typedef std::map<const std::string, ShaderAttribute*> VertexAttributesMap;

		enum ShaderType
		{
			VertexShader,
			FragmentShader
		};

		Shader(ShaderType type,const std::string& fileName);
		void initialize();
		void compile();
		virtual void addVertexAttribute(ShaderAttribute* attribute);
		static bool checkCompileStatus(unsigned int id,std::string& error);
		static void addShaderUniformConstant(const std::string& name, float value);
		const std::string name();
		unsigned int ID();

	protected:
		unsigned int toGLEnum();

	protected:
		ShaderType myType;
		unsigned int myID;
		std::string mySource;
		const std::string& myFileName;
		bool myIsCompiled;
		bool myInitialized;

		VertexAttributesMap myVertexAttributesMap;

		static bool myConstantsMapInitialized;
		static ConstantsMap myConstansMap;
	};
}
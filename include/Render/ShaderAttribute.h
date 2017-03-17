#pragma once
#include <string>
namespace vrv
{
	class ShaderAttribute
	{
	public:
		ShaderAttribute(std::string name, unsigned int location);
		unsigned int location();
		const std::string& name();
		virtual std::string typeToGLString() = 0;
	protected:
		std::string myName;
		unsigned int myLocation;
	};

	class ShaderAttributeInt : public ShaderAttribute
	{
	public:
		ShaderAttributeInt(std::string name, unsigned int location);
		std::string typeToGLString();
	};

	class ShaderAttributefloat : public ShaderAttribute
	{
	public:
		ShaderAttributefloat(std::string name, unsigned int location);
		std::string typeToGLString();
	};

	class ShaderAttributeVector3f : public ShaderAttribute
	{
	public:
		ShaderAttributeVector3f(std::string name, unsigned int location);
		std::string typeToGLString();
	};

	class ShaderAttributeVector4f : public ShaderAttribute
	{
	public:
		ShaderAttributeVector4f(std::string name, unsigned int location);
		std::string typeToGLString();
	};

}
#include <Render/ShaderAttribute.h>

namespace vrv
{
	ShaderAttribute::ShaderAttribute(std::string name, unsigned int location)
		: myName(name)
		, myLocation(location)
	{}

	unsigned int ShaderAttribute::location()
	{
		return myLocation;
	}

	const std::string& ShaderAttribute::name()
	{
		return myName;
	}

	ShaderAttributeInt::ShaderAttributeInt(std::string name, unsigned int location)
		: ShaderAttribute(name, location)
	{}
	std::string ShaderAttributeInt::typeToGLString()
	{
		return "int";
	}

	ShaderAttributefloat::ShaderAttributefloat(std::string name, unsigned int location)
		: ShaderAttribute(name, location)
	{}
	std::string ShaderAttributefloat::typeToGLString()
	{
		return "float";
	}

	ShaderAttributeVector3f::ShaderAttributeVector3f(std::string name, unsigned int location)
		: ShaderAttribute(name, location)
	{}
	std::string ShaderAttributeVector3f::typeToGLString()
	{
		return "vec3";
	}

	ShaderAttributeVector4f::ShaderAttributeVector4f(std::string name, unsigned int location)
		: ShaderAttribute(name, location)
	{}
	std::string ShaderAttributeVector4f::typeToGLString()
	{
		return "vec4";
	}
}
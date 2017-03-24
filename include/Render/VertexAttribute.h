#pragma once
#include <string>
#include <Render/Array.h>
namespace vrv
{
	class VertexAttribute
	{
	public:
		VertexAttribute(const std::string& name,Array::DataType type,unsigned int location);
		unsigned int location();
		const std::string& name();
		unsigned int baseType();
		unsigned int count();
		bool normalized();
		unsigned int stride();
		unsigned int offset();
		virtual std::string typeToGLSL() = 0;
	protected:
		std::string myName;
		Array::DataType myType;
		unsigned int myBaseType;
		unsigned int myLocation;
		unsigned int myCount;
		bool myNormalized;
		unsigned int myStride;
		unsigned int myOffset;
	};

	class VertexAttributeInt : public VertexAttribute
	{
	public:
		VertexAttributeInt(std::string name, unsigned int location);
		std::string typeToGLSL();
	};

	class VertexAttributefloat : public VertexAttribute
	{
	public:
		VertexAttributefloat(std::string name, unsigned int location);
		std::string typeToGLSL();
	};

	class VertexAttributeVector3f : public VertexAttribute
	{
	public:
		VertexAttributeVector3f(std::string name, unsigned int location);
		std::string typeToGLSL();
	};

	class VertexAttributeVector4f : public VertexAttribute
	{
	public:
		VertexAttributeVector4f(std::string name, unsigned int location);
		std::string typeToGLSL();
	};

}
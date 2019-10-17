#pragma once
#include <string>
#include <Render/Array.h>
namespace vrv
{
	class VertexAttribute
	{
	public:
		VertexAttribute(Array::DataType type,unsigned int location,
			unsigned int stride = 0, unsigned int offset = 0);
		unsigned int location();
		unsigned int baseType();
		unsigned int count();
		bool normalized();
		unsigned int stride();
		unsigned int offset();
		virtual std::string typeToGLSL() = 0;
	protected:
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
		VertexAttributeInt(unsigned int location, unsigned int stride = 0, unsigned int offset = 0);
		std::string typeToGLSL();
	};

	class VertexAttributefloat : public VertexAttribute
	{
	public:
		VertexAttributefloat(unsigned int location, unsigned int stride = 0, unsigned int offset = 0);
		std::string typeToGLSL();
	};

	class VertexAttributeVector2f : public VertexAttribute
	{
	public:
		VertexAttributeVector2f(unsigned int location, unsigned int stride = 0, unsigned int offset = 0);
		std::string typeToGLSL();
	};

	class VertexAttributeVector3f : public VertexAttribute
	{
	public:
		VertexAttributeVector3f(unsigned int location, unsigned int stride = 0, unsigned int offset = 0);
		std::string typeToGLSL();
	};

	class VertexAttributeVector4f : public VertexAttribute
	{
	public:
		VertexAttributeVector4f(unsigned int location, unsigned int stride = 0, unsigned int offset = 0);
		std::string typeToGLSL();
	};

}
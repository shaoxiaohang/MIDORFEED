#include <Render/VertexAttribute.h>
#include <Render/OpenGLContext.h>

namespace vrv
{
	VertexAttribute::VertexAttribute(Array::DataType type, unsigned int location,
		unsigned int stride, unsigned int offset)
		: myLocation(location)
		, myType(type)
		, myNormalized(false)
		, myStride(stride)
		, myOffset(offset)
	{
		switch (myType)
		{
		case vrv::Array::INT:
			myBaseType = GL_INT;
			myCount = 1;
			break;
		case vrv::Array::FLOAT:
			myBaseType = GL_FLOAT;
			myCount = 1;
			break;
		case vrv::Array::VEC2F:
			myBaseType = GL_FLOAT;
			myCount = 2;
			break;
		case vrv::Array::VEC3F:
			myBaseType = GL_FLOAT;
			myCount = 3;
			break;
		case vrv::Array::VEC4F:
			myBaseType = GL_FLOAT;
			myCount = 4;
			break;
		default:
			break;
		}
	}

	unsigned int VertexAttribute::location()
	{
		return myLocation;
	}

	unsigned int VertexAttribute::baseType()
	{
		return myBaseType;
	}

	unsigned int VertexAttribute::count()
	{
		return myCount;
	}

	bool VertexAttribute::normalized()
	{
		return myNormalized;
	}

	unsigned int VertexAttribute::stride()
	{
		return myStride;
	}

	unsigned int VertexAttribute::offset()
	{
		return myOffset;
	}

	VertexAttributeInt::VertexAttributeInt(unsigned int location, unsigned int stride, unsigned int offset)
		: VertexAttribute(Array::INT,location, stride, offset)
	{}
	std::string VertexAttributeInt::typeToGLSL()
	{
		return "int";
	}

	VertexAttributefloat::VertexAttributefloat(unsigned int location, unsigned int stride, unsigned int offset)
		: VertexAttribute(Array::FLOAT, location, stride,offset)
	{}
	std::string VertexAttributefloat::typeToGLSL()
	{
		return "float";
	}

	VertexAttributeVector2f::VertexAttributeVector2f(unsigned int location, unsigned int stride, unsigned int offset)
		: VertexAttribute(Array::VEC2F, location, stride,offset)
	{}

	std::string VertexAttributeVector2f::typeToGLSL()
	{
		return "vec2";
	}

	VertexAttributeVector3f::VertexAttributeVector3f(unsigned int location, unsigned int stride, unsigned int offset)
		: VertexAttribute(Array::VEC3F, location, stride, offset)
	{}
	std::string VertexAttributeVector3f::typeToGLSL()
	{
		return "vec3";
	}

	VertexAttributeVector4f::VertexAttributeVector4f(unsigned int location, unsigned int stride, unsigned int offset)
		: VertexAttribute(Array::VEC4F, location, stride, offset)
	{}
	std::string VertexAttributeVector4f::typeToGLSL()
	{
		return "vec4";
	}
}
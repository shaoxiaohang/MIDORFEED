//#include <Render/VertexAttribute.h>
//#include <GL/glew.h>
//namespace vrv
//{
//	VertexAttribute::VertexAttribute(const std::string& name, Array::DataType type, unsigned int location)
//		: myName(name)
//		, myLocation(location)
//		, myType(type)
//		, myNormalized(false)
//		, myStride(0)
//		, myOffset(0)
//	{
//		switch (myType)
//		{
//		case vrv::Array::INT:
//			myBaseType = GL_INT;
//			myCount = 1;
//			break;
//		case vrv::Array::FLOAT:
//			myBaseType = GL_FLOAT;
//			myCount = 1;
//			break;
//		case vrv::Array::VEC2F:
//			myBaseType = GL_FLOAT;
//			myCount = 2;
//			break;
//		case vrv::Array::VEC3F:
//			myBaseType = GL_FLOAT;
//			myCount = 3;
//			break;
//		case vrv::Array::VEC4F:
//			myBaseType = GL_FLOAT;
//			myCount = 4;
//			break;
//		default:
//			break;
//		}
//	}
//
//	unsigned int VertexAttribute::location()
//	{
//		return myLocation;
//	}
//
//	const std::string& VertexAttribute::name()
//	{
//		return myName;
//	}
//
//	unsigned int VertexAttribute::baseType()
//	{
//		return myBaseType;
//	}
//
//	unsigned int VertexAttribute::count()
//	{
//		return myCount;
//	}
//
//	bool VertexAttribute::normalized()
//	{
//		return myNormalized;
//	}
//
//	unsigned int VertexAttribute::stride()
//	{
//		return myStride;
//	}
//
//	unsigned int VertexAttribute::offset()
//	{
//		return myOffset;
//	}
//
//	VertexAttributeInt::VertexAttributeInt(std::string name, unsigned int location)
//		: VertexAttribute(name, Array::INT,location)
//	{}
//	std::string VertexAttributeInt::typeToGLSL()
//	{
//		return "int";
//	}
//
//	VertexAttributefloat::VertexAttributefloat(std::string name, unsigned int location)
//		: VertexAttribute(name, Array::FLOAT, location)
//	{}
//	std::string VertexAttributefloat::typeToGLSL()
//	{
//		return "float";
//	}
//
//	VertexAttributeVector3f::VertexAttributeVector3f(std::string name, unsigned int location)
//		: VertexAttribute(name, Array::VEC3F, location)
//	{}
//	std::string VertexAttributeVector3f::typeToGLSL()
//	{
//		return "vec3";
//	}
//
//	VertexAttributeVector4f::VertexAttributeVector4f(std::string name, unsigned int location)
//		: VertexAttribute(name, Array::VEC4F, location)
//	{}
//	std::string VertexAttributeVector4f::typeToGLSL()
//	{
//		return "vec4";
//	}
//}
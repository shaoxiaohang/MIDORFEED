#include <Render/Shader.h>
#include <Render/VertexAttribute.h>
#include <Render/OpenGLContext.h>
#include <Core/Utility.h>
#include <fstream>
#include <sstream>

namespace vrv
{
	Shader::Shader(ShaderType type, const std::string& fileName)
		: myType(type)
		, myFileName(fileName)
		, myInitialized(false)
		, myIsCompiled(false)
	{
		std::ifstream shaderFile;
		shaderFile.open(fileName.c_str());
		if (shaderFile.fail())
		{
			VRV_ERROR("failt to open " + fileName);
		}
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		mySource = shaderStream.str();
	}

	void Shader::initialize()
	{
		if (!myInitialized)
		{
			myID = OpenGLContext::instance().glCreateShader(toGLEnum());
			const GLchar* src = mySource.c_str();
         OpenGLContext::instance().glShaderSource(myID, 1, &src, 0);
			myInitialized = true;
		}
	}

	void Shader::compile()
	{
		if (!myIsCompiled)
		{
         OpenGLContext::instance().glCompileShader(myID);
			myIsCompiled = true;
		}
	}

	bool Shader::checkCompileStatus(unsigned int id, std::string& error)
	{
		int res;
      OpenGLContext::instance().glGetShaderiv(id, GL_COMPILE_STATUS, &res);
		if (res != GL_TRUE)
		{
			int infoLength = 0;
         OpenGLContext::instance().glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLength);
			char* str = new char[infoLength];
         OpenGLContext::instance().glGetShaderInfoLog(id, infoLength, 0, str);
			error = str;
			delete[] str;
			return false;
		}
		return true;
	}

	const std::string Shader::name()
	{
		return myFileName;
	}

	unsigned int Shader::ID()
	{
		return myID;
	}

	unsigned int Shader::toGLEnum()
	{
		switch (myType)
		{
		case vrv::Shader::VertexShader:
			return GL_VERTEX_SHADER;
			break;
		case vrv::Shader::FragmentShader:
			return GL_FRAGMENT_SHADER;
			break;
		case vrv::Shader::GeometryShader:
			return GL_GEOMETRY_SHADER;
			break;
		default:
			break;
		}
	}
}
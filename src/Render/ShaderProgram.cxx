#include <Render/ShaderProgram.h>
#include <Render/Shader.h>
#include <Core/UsefulMarco.h>
#include <sstream>
#include <GL/glew.h>
namespace vrv
{
	ShaderProgram::ShaderProgram(const std::string& vertFile, const std::string& fragFile)
	{
		myVertShader = new Shader(Shader::VertexShader, vertFile);
		myFragShader = new Shader(Shader::FragmentShader, fragFile);
	}

	ShaderProgram::ShaderProgram(const Shader* vert, const Shader* frag)
	{
		myVertShader = new Shader(*vert);
		myFragShader = new Shader(*frag);
	}

	ShaderProgram::~ShaderProgram()
	{
		delete myVertShader;
		delete myFragShader;
		glDeleteProgram(myID);
	}

	bool ShaderProgram::operator < (const ShaderProgram& pro)
	{
		return true;
	}
	bool ShaderProgram::operator > (const ShaderProgram& pro)
	{
		return true;
	}

	bool ShaderProgram::checkProgramLinkStatus(unsigned int id, std::string& error)
	{
		int res;
		glGetProgramiv(id, GL_LINK_STATUS, &res);
		if (res != GL_TRUE)
		{
			int infoLengh;
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLengh);
			char* info = new char[infoLengh];
			glGetProgramInfoLog(id, infoLengh, &infoLengh, info);
			error = info;
			delete[] info;
			return false;
		}
		return true;
	}

	void ShaderProgram::link()
	{
		myID = glCreateProgram();
		myVertID = myVertShader->createShader();
		myFragID = myFragShader->createShader();
		glCompileShader(myVertID);
		std::string info;
		if (!Shader::checkCompileStatus(myVertID, info))
		{
			std::stringstream ss;
			ss << myVertShader->name() << " comiling failed" << std::endl;
			ss << info << std::endl;
			VRV_ERROR(ss.str());
		}
		glCompileShader(myFragID);
		if (!Shader::checkCompileStatus(myFragID,info))
		{
			std::stringstream ss;
			ss << myFragShader->name() << " comiling failed" << std::endl;
			ss << info << std::endl;
			VRV_ERROR(ss.str());
		}
		glAttachShader(myID, myVertID);
		glAttachShader(myID, myFragID);
		glLinkProgram(myID);
		if (!checkProgramLinkStatus(myID,info))
		{
			std::stringstream ss;
			ss << "shader program"<< " comiling failed" << std::endl;
			ss << info << std::endl;
			VRV_ERROR(ss.str());
		}
	}
}
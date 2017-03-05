#include <Render/ShaderProgram.h>
#include <Render/Shader.h>
#include <Core/UsefulMarco.h>
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

	bool ShaderProgram::checkProgramLinkStatus(unsigned int id)
	{
		int res;
		glGetProgramiv(id, GL_LINK_STATUS, &res);
		return (res == GL_TRUE)? true:false;
	}

	void ShaderProgram::link()
	{
		myID = glCreateProgram();
		myVertID = myVertShader->createShader();
		myFragID = myFragShader->createShader();
		glAttachShader(GL_VERTEX_SHADER, myVertID);
		glAttachShader(GL_FRAGMENT_SHADER, myFragID);
		glCompileShader(myVertID);
		if (!Shader::checkCompileStatus(myVertID))
		{
			VRV_ERROR("vertex shader compiling failed");
		}
		glCompileShader(myFragID);
		if (!Shader::checkCompileStatus(myFragID))
		{
			VRV_ERROR("fragment shader compiling failed");
		}
		glLinkProgram(myID);
		if (!checkProgramLinkStatus(myID))
		{
			VRV_ERROR("shader program link failed");
		}
	}
}
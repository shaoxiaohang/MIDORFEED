#include <Render/ShaderProgram.h>
#include <Render/Shader.h>
#include <Render/ShaderAttribute.h>
#include <Core/UsefulMarco.h>
#include <sstream>
#include <GL/glew.h>
namespace vrv
{
	bool ShaderProgram::myAutomaticUniformsFactoryInitialized = false;

	ShaderProgram::ShaderProgram(const std::string& vertFile, const std::string& fragFile)
	{
		if (myAutomaticUniformsFactoryInitialized == false)
		{
			registerAutomaticUniformFactories();
			myAutomaticUniformsFactoryInitialized = true;
		}
		myVertShader = new Shader(Shader::VertexShader, vertFile);
		myFragShader = new Shader(Shader::FragmentShader, fragFile);
		myVertShader->addVertexAttribute(new ShaderAttributeInt("alpha",0));
		myVertShader->addVertexAttribute(new ShaderAttributeVector3f("position", 1));
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

	Shader* ShaderProgram::vertexShader()
	{
		return myVertShader;
	}

	Shader* ShaderProgram::fragmentShader()
	{
		return myFragShader;
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

	ShaderUniform* ShaderProgram::createUniform(std::string name, ShaderUniform::UniformType type)
	{
		switch (type)
		{
		case vrv::ShaderUniform::FLOAT:
			return new ShaderUniformFloat(name);
			break;
		case vrv::ShaderUniform::FLOAT_VEC2:
			return new ShaderUniformVec2f(name);
			break;
		case vrv::ShaderUniform::FLOAT_VEC3:
			return new ShaderUniformVec3f(name);
			break;
		case vrv::ShaderUniform::FLOAT_VEC4:
			return new ShaderUniformVec4f(name);
			break;
		case vrv::ShaderUniform::INT:
			return new ShaderUniformInt(name);
			break;
		case vrv::ShaderUniform::BOOL:
			return new ShaderUniformBool(name);
			break;
		case vrv::ShaderUniform::FLOAT_MAT3:
			return new ShaderUniformMat3f(name);
			break;
		case vrv::ShaderUniform::FLOAT_MAT4:
			return new ShaderUniformMat4f(name);
			break;
		default:
			return new ShaderUniformFloat(name);
			break;
		}
	}

	void ShaderProgram::updateUniforms()
	{
		UniformMap::iterator ibegin = myUniformsMap.begin();
		UniformMap::iterator iend = myUniformsMap.end();
		for (; ibegin != iend; ++ibegin)
		{
			ShaderUniform* uniform = ibegin->second;
			if (uniform && uniform->isDirty())
			{
				uniform->synGL();
			}
		}
	}

	void ShaderProgram::link()
	{
		myID = glCreateProgram();
		myVertShader->initialize();
		myFragShader->initialize();
		myVertShader->compile();
		std::string info;
		if (!Shader::checkCompileStatus(myVertShader->ID(), info))
		{
			std::stringstream ss;
			ss << myVertShader->name() << " compile failed" << std::endl;
			ss << info << std::endl;
			VRV_ERROR(ss.str());
		}
		myFragShader->compile();
		if (!Shader::checkCompileStatus(myFragShader->ID(), info))
		{
			std::stringstream ss;
			ss << myFragShader->name() << " compile failed" << std::endl;
			ss << info << std::endl;
			VRV_ERROR(ss.str());
		}
		glAttachShader(myID, myVertShader->ID());
		glAttachShader(myID, myFragShader->ID());
		glLinkProgram(myID);
		if (!checkProgramLinkStatus(myID,info))
		{
			std::stringstream ss;
			ss << "shader program"<< " comiling failed" << std::endl;
			ss << info << std::endl;
			VRV_ERROR(ss.str());
		}
		populateUniforms();
	}

	void ShaderProgram::populateUniforms()
	{
		clearUniforms();
		int totalUniforms = 0;
		glGetProgramiv(myID, GL_ACTIVE_UNIFORMS, &totalUniforms);
		if (totalUniforms == 0)
		{
			return;
		}
		else
		{
			int maxNameLength;
			glGetProgramiv(myID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);
			int uniformSize;
			GLenum uniformType;
			char* uniformName = new char[maxNameLength];
			for (unsigned int i = 0; i < totalUniforms;++i)
			{
				glGetActiveUniform(myID, i, maxNameLength, NULL, &uniformSize, &uniformType, uniformName);
				myUniformsMap.insert(std::make_pair(uniformName, createUniform(uniformName, ShaderUniform::mapGLToUniformType(uniformType))));
			}
		}
	}

	void ShaderProgram::populateAutomaticUniforms()
	{
		UniformMap::iterator ibegin = myUniformsMap.begin();
		UniformMap::iterator iend = myUniformsMap.end();
		std::vector<std::string>::iterator itor;
		for (; ibegin != iend; ++ibegin)
		{
			std::string name = ibegin->first;
			AutomaticUniformFactoryMap::iterator factoryItor = myAutomaticUniformFactories.find(name);
			if (factoryItor != myAutomaticUniformFactories.end())
			{
				myAutomaticUniformsMap.insert(std::make_pair(name, factoryItor->second->create()));
			}
		}
	}

	void ShaderProgram::clearUniforms()
	{
		UniformMap::iterator ibegin = myUniformsMap.begin();
		UniformMap::iterator iend = myUniformsMap.end();
		for (; ibegin != iend; ++ibegin)
		{
			if (ibegin->second)
			{
				delete ibegin->second;
			}
		}
		myUniformsMap.clear();
	}

	void ShaderProgram::registerAutomaticUniformFactories()
	{
		myAutomaticUniformFactories.insert(std::make_pair("vrv_view_matrix", new CameraViewMatrixUniformFactory()));
	}
}
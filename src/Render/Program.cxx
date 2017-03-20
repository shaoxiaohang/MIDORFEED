#include <Render/Program.h>
#include <Render/Shader.h>
#include <Render/VertexAttribute.h>
#include <Core/UsefulMarco.h>
#include <sstream>
#include <GL/glew.h>
namespace vrv
{
	bool Program::myAutomaticUniformsFactoryInitialized = false;
	Program::AutomaticUniformFactoryMap Program::myAutomaticUniformFactories;

	Program::Program(const std::string& vertFile, const std::string& fragFile)
	{
		if (myAutomaticUniformsFactoryInitialized == false)
		{
			registerAutomaticUniformFactories();
			myAutomaticUniformsFactoryInitialized = true;
		}
		myVertShader = new Shader(Shader::VertexShader, vertFile);
		myFragShader = new Shader(Shader::FragmentShader, fragFile);
	}

	Program::Program(const Shader* vert, const Shader* frag)
	{
		myVertShader = new Shader(*vert);
		myFragShader = new Shader(*frag);
	}

	Program::~Program()
	{
		delete myVertShader;
		delete myFragShader;
		glDeleteProgram(myID);
	}

	Shader* Program::vertexShader()
	{
		return myVertShader;
	}

	Shader* Program::fragmentShader()
	{
		return myFragShader;
	}

	bool Program::operator < (const Program& pro)
	{
		return true;
	}
	bool Program::operator > (const Program& pro)
	{
		return true;
	}

	bool Program::checkProgramLinkStatus(unsigned int id, std::string& error)
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

	Uniform* Program::createUniform(std::string name, Uniform::UniformType type)
	{
		switch (type)
		{
		case vrv::Uniform::FLOAT:
			return new UniformFloat(name);
			break;
		case vrv::Uniform::FLOAT_VEC2:
			return new UniformVec2f(name);
			break;
		case vrv::Uniform::FLOAT_VEC3:
			return new UniformVec3f(name);
			break;
		case vrv::Uniform::FLOAT_VEC4:
			return new UniformVec4f(name);
			break;
		case vrv::Uniform::INT:
			return new UniformInt(name);
			break;
		case vrv::Uniform::BOOL:
			return new UniformBool(name);
			break;
		case vrv::Uniform::FLOAT_MAT3:
			return new UniformMat3f(name);
			break;
		case vrv::Uniform::FLOAT_MAT4:
			return new UniformMat4f(name);
			break;
		default:
			return new UniformFloat(name);
			break;
		}
	}

	void Program::updateUniforms()
	{
		UniformMap::iterator ibegin = myUniformsMap.begin();
		UniformMap::iterator iend = myUniformsMap.end();
		for (; ibegin != iend; ++ibegin)
		{
			Uniform* uniform = ibegin->second;
			if (uniform && uniform->isDirty())
			{
				uniform->synGL();
			}
		}
	}

	void Program::use()
	{
		glUseProgram(myID);
	}

	void Program::unuse()
	{
		glUseProgram(0);
	}

	void Program::link()
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

	void Program::populateUniforms()
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
				myUniformsMap.insert(std::make_pair(uniformName, createUniform(uniformName, Uniform::mapGLToUniformType(uniformType))));
			}
		}
	}

	void Program::populateAutomaticUniforms()
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

	void Program::clearUniforms()
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

	void Program::registerAutomaticUniformFactories()
	{
		myAutomaticUniformFactories.insert(std::make_pair("vrv_view_matrix", new CameraViewMatrixUniformFactory()));
	}
}
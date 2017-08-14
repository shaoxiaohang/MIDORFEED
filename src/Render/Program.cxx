#include <Render/Program.h>
#include <Render/Shader.h>
#include <Render/VertexAttribute.h>
#include <Core/Utility.h>
#include <sstream>
#include <Render/QtContext.h>
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
		QtContext::instance().glDeleteProgram(myID);
	}

	Shader* Program::vertexShader() const
	{
		return myVertShader;
	}
	 
	Shader* Program::fragmentShader() const
	{
		return myFragShader;
	}

	bool Program::operator < (const Program& pro)
	{
		if (myVertShader != pro.vertexShader() || myFragShader != pro.fragmentShader())
		{
			return true;
		}
		return false;
	}


	bool Program::checkProgramLinkStatus(unsigned int id, std::string& error)
	{
		int res;
		QtContext::instance().glGetProgramiv(id, GL_LINK_STATUS, &res);
		if (res != GL_TRUE)
		{
			int infoLengh;
			QtContext::instance().glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLengh);
			char* info = new char[infoLengh];
			QtContext::instance().glGetProgramInfoLog(id, infoLengh, &infoLengh, info);
			error = info;
			delete[] info;
			return false;
		}
		return true;
	}

	Uniform* Program::createUniform(std::string name, Uniform::UniformType type,int location)
	{
		switch (type)
		{
		case vrv::Uniform::FLOAT:
			return new UniformFloat(name, location);
			break;
		case vrv::Uniform::FLOAT_VEC2:
			return new UniformVec2f(name, location);
			break;
		case vrv::Uniform::FLOAT_VEC3:
			return new UniformVec3f(name, location);
			break;
		case vrv::Uniform::FLOAT_VEC4:
			return new UniformVec4f(name, location);
			break;
		case vrv::Uniform::INT:
			return new UniformInt(name, location);
			break;
		case vrv::Uniform::BOOL:
			return new UniformBool(name, location);
			break;
		case vrv::Uniform::FLOAT_MAT3:
			return new UniformMat3f(name, location);
			break;
		case vrv::Uniform::FLOAT_MAT4:
			return new UniformMat4f(name, location);
			break;
		case vrv::Uniform::SAMPLER_2D:
			return new UniformInt(name, location);
			break;
		default:
			return new UniformFloat(name, location);
			break;
		}
	}

	Uniform* Program::getUniform(std::string name)
	{
		if (myUniformsMap.find(name) != myUniformsMap.end())
		{
			return myUniformsMap[name];
		}
		return 0;
	}

	void Program::updateAutomaticUniforms(Scene* scene)
	{
		AutomaticUniformMap::iterator ibegin = myAutomaticUniformsMap.begin();
		AutomaticUniformMap::iterator iend   = myAutomaticUniformsMap.end();
		for (; ibegin != iend; ++ibegin)
		{
			AutomaticUniform* automaticUniform = ibegin->second;
			automaticUniform->synGL(scene);
		}
	}

	void Program::updateUniforms()
	{
		use();
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
		QtContext::instance().glUseProgram(myID);
	}

	void Program::unuse()
	{
		QtContext::instance().glUseProgram(0);
	}

	void Program::link()
	{
		myID = QtContext::instance().glCreateProgram();
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
		QtContext::instance().glAttachShader(myID, myVertShader->ID());
		QtContext::instance().glAttachShader(myID, myFragShader->ID());
		QtContext::instance().glLinkProgram(myID);
		if (!checkProgramLinkStatus(myID,info))
		{
			std::stringstream ss;
			ss << "shader program"<< " comiling failed" << std::endl;
			ss << info << std::endl;
			VRV_ERROR(ss.str());
		}
		populateUniforms();
		populateAutomaticUniforms();
	}

	void Program::populateUniforms()
	{
		clearUniforms();
		int totalUniforms = 0;
		QtContext::instance().glGetProgramiv(myID, GL_ACTIVE_UNIFORMS, &totalUniforms);
		if (totalUniforms == 0)
		{
			return;
		}
		else
		{
			int maxNameLength;
			QtContext::instance().glGetProgramiv(myID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);
			int uniformSize;
			GLenum uniformType;
			char* uniformName = new char[maxNameLength];
			int location = -1;
			for (unsigned int i = 0; i < totalUniforms;++i)
			{
				QtContext::instance().glGetActiveUniform(myID, i, maxNameLength, NULL, &uniformSize, &uniformType, uniformName);
				location = QtContext::instance().glGetUniformLocation(myID, uniformName);
				myUniformsMap.insert(std::make_pair(uniformName, createUniform(uniformName, Uniform::mapGLToUniformType(uniformType), location)));
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
				myAutomaticUniformsMap.insert(std::make_pair(name, factoryItor->second->create(ibegin->second)));
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
		myAutomaticUniformFactories.insert(std::make_pair("vrv_view_pos", new CameraPositionUniformFactory()));
		myAutomaticUniformFactories.insert(std::make_pair("vrv_view_matrix", new CameraViewMatrixUniformFactory()));
		myAutomaticUniformFactories.insert(std::make_pair("vrv_proj_matrix", new CameraProjMatrixUniformFactory()));
	}
}
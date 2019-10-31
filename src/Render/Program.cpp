#include <Render/Program.h>
#include <Render/Shader.h>
#include <Render/Scene.h>
#include <Core/Utility.h>
#include <sstream>
#include <Render/OpenGLContext.h>
namespace vrv
{
	bool Program::myAutomaticUniformsFactoryInitialized = false;
	Program::AutomaticUniformFactoryMap Program::myAutomaticUniformFactories;
	
	bool Program::myUniformBufferObjectInitialized = false;
	UniformBufferObject* Program::myUniformBufferObject = 0;

	Program::Program(const std::string& vertFile, const std::string& fragFile, std::string geometry)
		: myGeometryShader(0)
	{
		if (myAutomaticUniformsFactoryInitialized == false)
		{
			registerAutomaticUniformFactories();
			myAutomaticUniformsFactoryInitialized = true;
		}
		if (myUniformBufferObjectInitialized == false)
		{
			setUpUniformBufferObject();
			myUniformBufferObjectInitialized = true;
		}
		myVertShader = new Shader(Shader::VertexShader, vertFile);
		myFragShader = new Shader(Shader::FragmentShader, fragFile);
		if (geometry != "")
		{
			myGeometryShader = new Shader(Shader::GeometryShader, geometry);
		}
		link();
	}

	Program::Program(const Shader* vert, const Shader* frag)
		: myGeometryShader(0)
	{
		myVertShader = new Shader(*vert);
		myFragShader = new Shader(*frag);
		link();
	}

	Program::Program(Shader* vert, Shader* frag, Shader* geom)
		: myVertShader(vert)
		, myFragShader(frag)
		, myGeometryShader(geom)
	{
		link();
	}

	Program::~Program()
	{
		delete myVertShader;
		delete myFragShader;
      OpenGLContext::instance().glDeleteProgram(myID);
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
      OpenGLContext::instance().glGetProgramiv(id, GL_LINK_STATUS, &res);
		if (res != GL_TRUE)
		{
			int infoLengh;
         OpenGLContext::instance().glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLengh);
			char* info = new char[infoLengh];
         OpenGLContext::instance().glGetProgramInfoLog(id, infoLengh, &infoLengh, info);
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
		case vrv::Uniform::SAMPLER_CUBE:
			return new UniformInt(name, location);
			break;
		default:
			VRV_ERROR("unsupported uniform" + name)
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

		myUniformBufferObject->update();

	}

	void Program::use()
	{
      OpenGLContext::instance().glUseProgram(myID);
	}

	void Program::unuse()
	{
      OpenGLContext::instance().glUseProgram(0);
	}

	void Program::bindUniformBufferToPoint(const std::string& uniformBuffer, int point)
	{
		unsigned int index = OpenGLContext::instance().glGetUniformBlockIndex(myID, uniformBuffer.c_str());
      OpenGLContext::instance().glUniformBlockBinding(myID, index, point);
	}

	void Program::set(const std::string& uniform, bool value)
	{
		if (getUniform(uniform))
		{
			getUniform(uniform)->set(value);
		}
	}

	void Program::set(const std::string& uniform, unsigned int value)
	{
		if (getUniform(uniform))
		{
			getUniform(uniform)->set(value);
		}
	}

	void Program::set(const std::string& uniform, int value)
	{
		if (getUniform(uniform))
		{
			getUniform(uniform)->set(value);
		}
	}

	void Program::set(const std::string& uniform, float value)
	{
		if (getUniform(uniform))
		{
			getUniform(uniform)->set(value);
		}
	}

	void Program::set(const std::string& uniform, Vector2f value)
	{
		if (getUniform(uniform))
		{
			getUniform(uniform)->set(value);
		}
	}

	void Program::set(const std::string& uniform, Vector3f value)
	{
		if (getUniform(uniform))
		{
			getUniform(uniform)->set(value);
		}
	}

	void Program::set(const std::string& uniform, Vector4f value)
	{
		if (getUniform(uniform))
		{
			getUniform(uniform)->set(value);
		}
	}

	void Program::set(const std::string& uniform, Matrix3f value)
	{
		if (getUniform(uniform))
		{
			getUniform(uniform)->set(value);
		}
	}

	void Program::set(const std::string& uniform, Matrix4f value)
	{
		if (getUniform(uniform))
		{
			getUniform(uniform)->set(value);
		}
	}

	void Program::link()
	{
		myID = OpenGLContext::instance().glCreateProgram();
		myVertShader->initialize();
		myFragShader->initialize();

		if (myGeometryShader)
		{
			myGeometryShader->initialize();
		}

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

		if (myGeometryShader)
		{
			myGeometryShader->compile();
			if (!Shader::checkCompileStatus(myGeometryShader->ID(), info))
			{
				std::stringstream ss;
				ss << myGeometryShader->name() << " compile failed" << std::endl;
				ss << info << std::endl;
				VRV_ERROR(ss.str());
			}
		}

      OpenGLContext::instance().glAttachShader(myID, myVertShader->ID());
      OpenGLContext::instance().glAttachShader(myID, myFragShader->ID());
		if (myGeometryShader)
		{
         OpenGLContext::instance().glAttachShader(myID, myGeometryShader->ID());
		}

      OpenGLContext::instance().glLinkProgram(myID);
		if (!checkProgramLinkStatus(myID,info))
		{
			std::stringstream ss;
			ss << "shader program"<< " comiling failed" << std::endl;
         ss << "vertex shader" << myVertShader->name() << std::endl;
         ss << "fragment shader" << myFragShader->name() << std::endl;
			ss << info << std::endl;
			VRV_ERROR(ss.str());
		}
		populateUniforms();
	}

	void Program::populateUniforms()
	{
		clearUniforms();
		int totalUniforms = 0;
      OpenGLContext::instance().glGetProgramiv(myID, GL_ACTIVE_UNIFORMS, &totalUniforms);
		if (totalUniforms == 0)
		{
			return;
		}
		else
		{
			int maxNameLength;
         OpenGLContext::instance().glGetProgramiv(myID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);
			int uniformSize;
			GLenum uniformType;
			char* uniformName = new char[maxNameLength];
			int location = -1;
			for (int i = 0; i < totalUniforms;++i)
			{
            OpenGLContext::instance().glGetActiveUniform(myID, i, maxNameLength, NULL, &uniformSize, &uniformType, uniformName);
				location = OpenGLContext::instance().glGetUniformLocation(myID, uniformName);

				AutomaticUniformFactoryMap::iterator factoryItor = myAutomaticUniformFactories.find(uniformName);
				Uniform* uniform = createUniform(uniformName, Uniform::mapGLToUniformType(uniformType), location);
				if (factoryItor == myAutomaticUniformFactories.end())
				{
					myUniformsMap.insert(std::make_pair(uniformName, uniform));
				}		
			}
		}

		bindUniformBufferToPoint("CameraUBO", 0);
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

	void Program::setUpUniformBufferObject()
	{
		myUniformBufferObject = new UniformBufferObject();

		AutomaticUniformFactoryMap::iterator iter = myAutomaticUniformFactories.begin();
		AutomaticUniformFactoryMap::iterator end = myAutomaticUniformFactories.end();
		for (; iter != end; ++iter)
		{
			myUniformBufferObject->addAutomaticUniform(iter->second->create());
		}
		
		myUniformBufferObject->build();
		myUniformBufferObject->bindToPoint(0);
	}
}
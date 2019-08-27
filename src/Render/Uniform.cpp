#include <Render/Uniform.h>
#include <Render/Scene.h>
#include <Render/Camera.h>
#include <Render/OpenGLContext.h>
#include <Core/Utility.h>
namespace vrv
{
	Uniform::UniformType Uniform::mapGLToUniformType(unsigned int glenum)
	{
		switch (glenum)
		{
		case GL_FLOAT:
			return FLOAT;
		case GL_FLOAT_VEC2:
			return FLOAT_VEC2;
		case GL_FLOAT_VEC3:
			return FLOAT_VEC3;
		case GL_FLOAT_VEC4:
			return FLOAT_VEC4;
		case GL_INT:
			return INT;
		case GL_BOOL:
			return BOOL;
		case GL_FLOAT_MAT3:
			return FLOAT_MAT3;
		case GL_FLOAT_MAT4:
			return FLOAT_MAT4;
		case GL_SAMPLER_2D:
			return SAMPLER_2D;
		case GL_SAMPLER_CUBE:
			return SAMPLER_CUBE;
		default:
			VRV_ERROR("unsupported uniform type")
			break;
		}
	}

	Uniform::Uniform()
	{}

	Uniform::Uniform(const std::string& name, UniformType type, int location)
		: myName(name)
		, myType(type)
		, myIsDirty(true)
		, myLocation(location)
	{}

	void Uniform::synGL()
	{
		myIsDirty = false;
	}

	int Uniform::location()
	{
		return myLocation;
	}

	int Uniform::size()
	{
		switch (myType)
		{
		case Uniform::FLOAT:
			return sizeof(float);
			break;
		case Uniform::FLOAT_VEC2:
			return 2*sizeof(float);
			break;
		case Uniform::FLOAT_VEC3:
			return 3*sizeof(float);
			break;
		case Uniform::FLOAT_VEC4:
			return 4*sizeof(float);
			break;
		case Uniform::UNSIGNED_INT:
			return sizeof(unsigned);
			break;
		case Uniform::INT:
			return sizeof(int);
			break;
		case Uniform::BOOL:
			return sizeof(bool);
			break;
		case Uniform::FLOAT_MAT3:
			return 9*sizeof(float);
			break;
		case Uniform::FLOAT_MAT4:
			return 16*sizeof(float);
			break;
		case Uniform::SAMPLER_2D:
			return sizeof(unsigned);
			break;
		case Uniform::SAMPLER_CUBE:
			return sizeof(unsigned);
			break;
		default:
			break;
		}
	}

	bool Uniform::isDirty()
	{
		return myIsDirty;
	}

	bool Uniform::set(bool value)
	{
		return false;
	}

	bool Uniform::set(unsigned int value)
	{
		return false;
	}

	bool Uniform::set(int value)
	{
		return false;
	}
	bool Uniform::set(float value)
	{
		return false;
	}
	bool Uniform::set(Vector2f value)
	{
		return false;
	}
	bool Uniform::set(Vector3f value)
	{
		return false;
	}
	bool Uniform::set(Vector4f value)
	{
		return false;
	}
	bool Uniform::set(Matrix3f value)
	{
		return false;
	}
	bool Uniform::set(Matrix4f value)
	{
		return false;
	}

	bool Uniform::get(bool& value)
	{
		return false;
	}
	bool Uniform::get(unsigned int& value)
	{
		return false;
	}
	bool Uniform::get(int& value)
	{
		return false;
	}
	bool Uniform::get(float& value)
	{
		return false;
	}
	bool Uniform::get(Vector2f& value)
	{
		return false;
	}
	bool Uniform::get(Vector3f& value)
	{
		return false;
	}
	bool Uniform::get(Vector4f& value)
	{
		return false;
	}
	bool Uniform::get(Matrix3f& value)
	{
		return false;
	}
	bool Uniform::get(Matrix4f& value)
	{
		return false;
	}

	UniformBool::UniformBool(const std::string& name,int location)
		: Uniform(name, Uniform::BOOL, location)
		, myValue(false)
	{}
	bool UniformBool::set(bool value)
	{
		if (myValue != value)
		{
			myValue = value;
			myIsDirty = true;
		}
		return true;
	}
	bool UniformBool::get(bool& value)
	{
		value = myValue;
		return true;
	}
	void UniformBool::synGL()
	{
		Uniform::synGL();
		OpenGLContext::instance().glUniform1i(myLocation, myValue);
	}
	void* UniformBool::dataPointer()
	{
		return  &myValue;
	}

	UniformInt::UniformInt(const std::string& name, int location)
		: Uniform(name, Uniform::INT, location)
		, myValue(0)
	{}
	bool UniformInt::set(int value)
	{
		if (myValue != value)
		{
			myValue = value;
			myIsDirty = true;
		}
		return true;
	}
	bool UniformInt::get(int& value)
	{
		value = myValue;
		return true;
	}
	void UniformInt::synGL()
	{
		Uniform::synGL();
      OpenGLContext::instance().glUniform1i(myLocation, myValue);
	}
	void* UniformInt::dataPointer()
	{
		return  &myValue;
	}

	UniformUnsignedInt::UniformUnsignedInt(const std::string& name, int location)
		: Uniform(name, Uniform::UNSIGNED_INT, location)
	{}
	bool UniformUnsignedInt::set(unsigned int value)
	{
		if (myValue != value)
		{
			myValue = value;
			myIsDirty = true;
		}
		return true;
	}
	bool UniformUnsignedInt::get(unsigned int& value)
	{
		value = myValue;
		return true;
	}
	void UniformUnsignedInt::synGL()
	{
		Uniform::synGL();
      OpenGLContext::instance().glUniform1i(myLocation, myValue);
	}
	void* UniformUnsignedInt::dataPointer()
	{
		return  &myValue;
	}

	UniformFloat::UniformFloat(const std::string& name, int location)
		: Uniform(name, Uniform::FLOAT, location)
		, myValue(0)
	{}
	bool UniformFloat::set(float value)
	{
		if (myValue != value)
		{
			myValue = value;
			myIsDirty = true;
		}
		return true;
	}
	bool UniformFloat::get(float& value)
	{
		value = myValue;
		return true;
	}
	void UniformFloat::synGL()
	{
		Uniform::synGL();
      OpenGLContext::instance().glUniform1f(myLocation, myValue);
	}
	void* UniformFloat::dataPointer()
	{
		return  &myValue;
	}

	UniformVec2f::UniformVec2f(const std::string& name, int location)
		:Uniform(name, Uniform::FLOAT_VEC2, location)
	{}
	bool UniformVec2f::set(Vector2f value)
	{
		if (myValue != value)
		{
			myValue = value;
			myIsDirty = true;
		}
		return true;
	}
	bool UniformVec2f::get(Vector2f& value)
	{
		value = myValue;
		return true;
	}
	void UniformVec2f::synGL()
	{
		Uniform::synGL();
      OpenGLContext::instance().glUniform2f(myLocation, myValue.x(), myValue.y());
	}
	void* UniformVec2f::dataPointer()
	{
		return  &myValue;
	}

	UniformVec3f::UniformVec3f(const std::string& name, int location)
		:Uniform(name, Uniform::FLOAT_VEC3, location)
	{}
	bool UniformVec3f::set(Vector3f value)
	{
		if (myValue != value)
		{
			myValue = value;
			myIsDirty = true;
		}
		return true;
	}
	bool UniformVec3f::get(Vector3f& value)
	{
		value = myValue;
		return true;
	}
	void UniformVec3f::synGL()
	{
		Uniform::synGL();
      OpenGLContext::instance().glUniform3f(myLocation, myValue.x(), myValue.y(), myValue.z());
	}
	void* UniformVec3f::dataPointer()
	{
		return  &myValue;
	}

	UniformVec4f::UniformVec4f(const std::string& name, int location)
		:Uniform(name, Uniform::FLOAT_VEC4, location)
	{}
	bool UniformVec4f::set(Vector4f value)
	{
		if (myValue != value)
		{
			myValue = value;
			myIsDirty = true;
		}
		return true;
	}
	bool UniformVec4f::get(Vector4f& value)
	{
		value = myValue;
		return true;
	}
	void UniformVec4f::synGL()
	{
		Uniform::synGL();
      OpenGLContext::instance().glUniform4f(myLocation, myValue.x(), myValue.y(), myValue.z(), myValue.w());
	}
	void* UniformVec4f::dataPointer()
	{
		return &myValue;
	}

	UniformMat3f::UniformMat3f(const std::string& name, int location)
		:Uniform(name, Uniform::FLOAT_MAT3, location)
	{}
	bool UniformMat3f::set(Matrix3f value)
	{
		if (myValue != value)
		{
			myValue = value;
			myIsDirty = true;
		}
		return true;
	}
	bool UniformMat3f::get(Matrix3f& value)
	{
		value = myValue;
		return true;
	}
	void UniformMat3f::synGL()
	{
		Uniform::synGL();
      OpenGLContext::instance().glUniformMatrix3fv(myLocation, 1, false, &myValue.m[0]);
	}
	void* UniformMat3f::dataPointer()
	{
		return &myValue.m[0];
	}

	UniformMat4f::UniformMat4f(const std::string& name, int location)
		:Uniform(name, Uniform::FLOAT_MAT4, location)
	{}
	bool UniformMat4f::set(Matrix4f value)
	{
		if (myValue != value)
		{
			myValue = value;
			myIsDirty = true;
		}
		return true;
	}
	bool UniformMat4f::get(Matrix4f& value)
	{
		value = myValue;
		return true;
	}
	void UniformMat4f::synGL()
	{
		Uniform::synGL();
      OpenGLContext::instance().glUniformMatrix4fv(myLocation, 1, false, &myValue.m[0]);
	}
	void* UniformMat4f::dataPointer()
	{
		return &myValue.m[0];
	}


	AutomaticUniform::AutomaticUniform()
		: myUniform(0)
	{}

	Uniform* AutomaticUniform::uniform()
	{
		return myUniform;
	}

	AutomaticUniformFactory::AutomaticUniformFactory(const std::string& name)
		: myName(name)
	{}

	CameraPositionUniform::CameraPositionUniform(const std::string& name)
		: AutomaticUniform()
	{
		myUniform = new UniformVec3f(name,-1);
	}

	void CameraPositionUniform::update()
	{
		Scene* scene = Scene::instancePtr();
		if (scene && scene->masterCamera())
		{
			myUniform->set(scene->masterCamera()->position());
		}
	}

	CameraPositionUniformFactory::CameraPositionUniformFactory()
		: AutomaticUniformFactory("vrv_view_pos")
	{}

	AutomaticUniform* CameraPositionUniformFactory::create()
	{
		return new CameraPositionUniform(myName);
	}

	CameraViewMatrixUniform::CameraViewMatrixUniform(const std::string& name)
		: AutomaticUniform()
	{
		myUniform = new UniformMat4f(name, -1);
	}

	void CameraViewMatrixUniform::update()
	{
		Scene* scene = Scene::instancePtr();
		if (scene && scene->masterCamera())
		{
			myUniform->set(scene->masterCamera()->getViewMatrix());
		}
	}

	CameraViewMatrixUniformFactory::CameraViewMatrixUniformFactory()
		: AutomaticUniformFactory("vrv_view_matrix")
	{}

	AutomaticUniform* CameraViewMatrixUniformFactory::create()
	{
		return new CameraViewMatrixUniform(myName);
	}

	CameraProjMatrixUniform::CameraProjMatrixUniform(const std::string& name)
		: AutomaticUniform()
	{
		myUniform = new UniformMat4f(name, -1);
	}

	void CameraProjMatrixUniform::update()
	{
		Scene* scene = Scene::instancePtr();
		if (scene && scene->masterCamera())
		{
			myUniform->set(scene->masterCamera()->projectionMatrix());
		}
	}

	CameraProjMatrixUniformFactory::CameraProjMatrixUniformFactory()
		: AutomaticUniformFactory("vrv_proj_matrix")
	{}
    
	AutomaticUniform* CameraProjMatrixUniformFactory::create()
	{
		return new CameraProjMatrixUniform(myName);
	}
	
}
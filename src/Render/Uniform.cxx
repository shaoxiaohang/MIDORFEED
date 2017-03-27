#include<Render/Uniform.h>
#include<Render/QtContext.h>
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
		default:
			break;
		}
	}

	Uniform::Uniform()
	{}

	Uniform::Uniform(const std::string& name, UniformType type)
		: myName(name)
		, myType(type)
		, myIsDirty(true)
	{}

	bool Uniform::isDirty()
	{
		return myIsDirty;
	}

	bool Uniform::set(bool value)
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


	UniformBool::UniformBool(const std::string& name)
		:Uniform(name, Uniform::BOOL)
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
		QtContext::instance().glUniform1i(myLocation, myValue);
	}

	UniformInt::UniformInt(const std::string& name)
		:Uniform(name, Uniform::INT)
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
		QtContext::instance().glUniform1i(myLocation, myValue);
	}

	UniformFloat::UniformFloat(const std::string& name)
		:Uniform(name, Uniform::FLOAT)
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
		QtContext::instance().glUniform1f(myLocation, myValue);
	}

	UniformVec2f::UniformVec2f(const std::string& name)
		:Uniform(name, Uniform::FLOAT_VEC2)
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
		QtContext::instance().glUniform2f(myLocation, myValue.x, myValue.y);
	}

	UniformVec3f::UniformVec3f(const std::string& name)
		:Uniform(name, Uniform::FLOAT_VEC3)
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
		QtContext::instance().glUniform3f(myLocation, myValue.x, myValue.y, myValue.z);
	}

	UniformVec4f::UniformVec4f(const std::string& name)
		:Uniform(name, Uniform::FLOAT_VEC4)
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
		QtContext::instance().glUniform4f(myLocation, myValue.x, myValue.y, myValue.z, myValue.w);
	}

	UniformMat3f::UniformMat3f(const std::string& name)
		:Uniform(name, Uniform::FLOAT_MAT3)
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
		QtContext::instance().glUniformMatrix3fv(myLocation, 1, false, myValue.m);
	}

	UniformMat4f::UniformMat4f(const std::string& name)
		:Uniform(name, Uniform::FLOAT_MAT4)
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
		QtContext::instance().glUniformMatrix4fv(myLocation, 1, false, myValue.m);
		myIsDirty = false;
	}


	AutomaticUniform::AutomaticUniform(const std::string& name)
		: myName(name)
	{}

	AutomaticUniformFactory::AutomaticUniformFactory(const std::string& name)
		: myName(name)
	{}

	CameraViewMatrixUniform::CameraViewMatrixUniform(const std::string& name)
		: AutomaticUniform(name)
	{}

	void CameraViewMatrixUniform::synGL()
	{

	}

	CameraViewMatrixUniformFactory::CameraViewMatrixUniformFactory()
		: AutomaticUniformFactory("vrv_view_matrix")
	{
	}

	AutomaticUniform* CameraViewMatrixUniformFactory::create()
	{
		return new CameraViewMatrixUniform(myName);
	}
}
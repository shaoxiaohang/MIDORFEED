#include<Render/ShaderUniform.h>
#include<GL/glew.h>
namespace vrv
{
	ShaderUniform::UniformType ShaderUniform::mapGLToUniformType(unsigned int glenum)
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

	ShaderUniform::ShaderUniform(const std::string& name, UniformType type)
		: myName(name)
		, myType(type)
		, myIsDirty(true)
	{}

	bool ShaderUniform::isDirty()
	{
		return myIsDirty;
	}

	bool ShaderUniform::set(bool value)
	{
		return false;
	}
	bool ShaderUniform::set(int value)
	{
		return false;
	}
	bool ShaderUniform::set(float value)
	{
		return false;
	}
	bool ShaderUniform::set(Vector2f value)
	{
		return false;
	}
	bool ShaderUniform::set(Vector3f value)
	{
		return false;
	}
	bool ShaderUniform::set(Vector4f value)
	{
		return false;
	}
	bool ShaderUniform::set(Matrix3f value)
	{
		return false;
	}
	bool ShaderUniform::set(Matrix4f value)
	{
		return false;
	}

	bool ShaderUniform::get(bool& value)
	{
		return false;
	}
	bool ShaderUniform::get(int& value)
	{
		return false;
	}
	bool ShaderUniform::get(float& value)
	{
		return false;
	}
	bool ShaderUniform::get(Vector2f& value)
	{
		return false;
	}
	bool ShaderUniform::get(Vector3f& value)
	{
		return false;
	}
	bool ShaderUniform::get(Vector4f& value)
	{
		return false;
	}
	bool ShaderUniform::get(Matrix3f& value)
	{
		return false;
	}
	bool ShaderUniform::get(Matrix4f& value)
	{
		return false;
	}


	ShaderUniformBool::ShaderUniformBool(const std::string& name)
		:ShaderUniform(name, ShaderUniform::BOOL)
	{}
	bool ShaderUniformBool::set(bool value)
	{
		myValue = value;
		return true;
	}
	bool ShaderUniformBool::get(bool& value)
	{
		value = myValue;
		return true;
	}
	void ShaderUniformBool::synGL()
	{
		glUniform1i(myLocation, myValue);
	}

	ShaderUniformInt::ShaderUniformInt(const std::string& name)
		:ShaderUniform(name, ShaderUniform::INT)
	{}
	bool ShaderUniformInt::set(int value)
	{
		myValue = value;
		return true;
	}
	bool ShaderUniformInt::get(int& value)
	{
		value = myValue;
		return true;
	}
	void ShaderUniformInt::synGL()
	{
		glUniform1i(myLocation, myValue);
	}

	ShaderUniformFloat::ShaderUniformFloat(const std::string& name)
		:ShaderUniform(name, ShaderUniform::FLOAT)
	{}
	bool ShaderUniformFloat::set(float value)
	{
		myValue = value;
		return true;
	}
	bool ShaderUniformFloat::get(float& value)
	{
		value = myValue;
		return true;
	}
	void ShaderUniformFloat::synGL()
	{
		glUniform1f(myLocation, myValue);
	}

	ShaderUniformVec2f::ShaderUniformVec2f(const std::string& name)
		:ShaderUniform(name, ShaderUniform::FLOAT_VEC2)
	{}
	bool ShaderUniformVec2f::set(Vector2f value)
	{
		myValue = value;
		return true;
	}
	bool ShaderUniformVec2f::get(Vector2f& value)
	{
		value = myValue;
		return true;
	}
	void ShaderUniformVec2f::synGL()
	{
		glUniform2f(myLocation, myValue.x, myValue.y);
	}

	ShaderUniformVec3f::ShaderUniformVec3f(const std::string& name)
		:ShaderUniform(name, ShaderUniform::FLOAT_VEC3)
	{}
	bool ShaderUniformVec3f::set(Vector3f value)
	{
		myValue = value;
		return true;
	}
	bool ShaderUniformVec3f::get(Vector3f& value)
	{
		value = myValue;
		return true;
	}
	void ShaderUniformVec3f::synGL()
	{
		glUniform3f(myLocation, myValue.x, myValue.y, myValue.z);
	}

	ShaderUniformVec4f::ShaderUniformVec4f(const std::string& name)
		:ShaderUniform(name, ShaderUniform::FLOAT_VEC4)
	{}
	bool ShaderUniformVec4f::set(Vector4f value)
	{
		myValue = value;
		return true;
	}
	bool ShaderUniformVec4f::get(Vector4f& value)
	{
		value = myValue;
		return true;
	}
	void ShaderUniformVec4f::synGL()
	{
		glUniform4f(myLocation, myValue.x, myValue.y, myValue.z, myValue.w);
	}

	ShaderUniformMat3f::ShaderUniformMat3f(const std::string& name)
		:ShaderUniform(name, ShaderUniform::FLOAT_MAT3)
	{}
	bool ShaderUniformMat3f::set(Matrix3f value)
	{
		myValue = value;
		return true;
	}
	bool ShaderUniformMat3f::get(Matrix3f& value)
	{
		value = myValue;
		return true;
	}
	void ShaderUniformMat3f::synGL()
	{
		glUniformMatrix3fv(myLocation, 1, false, myValue.m);
	}

	ShaderUniformMat4f::ShaderUniformMat4f(const std::string& name)
		:ShaderUniform(name, ShaderUniform::FLOAT_MAT4)
	{}
	bool ShaderUniformMat4f::set(Matrix4f value)
	{
		myValue = value;
		return true;
	}
	bool ShaderUniformMat4f::get(Matrix4f& value)
	{
		value = myValue;
		return true;
	}
	void ShaderUniformMat4f::synGL()
	{
		glUniformMatrix4fv(myLocation, 1, false, myValue.m);
		myIsDirty = false;
	}


	AutomaticUniform::AutomaticUniform(const std::string& name)
		: myName(name)
		, myUniform(0)
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
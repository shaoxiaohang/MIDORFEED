#pragma once

#include <string>
#include <Core/Vector2.h>
#include <Core/Vector3.h>
#include <Core/Vector4.h>
#include <Core/Matrix3.h>
#include <Core/Matrix4.h>
namespace vrv
{
	class ShaderProgram;
	class ShaderUniform
	{
	public:
		enum UniformType
		{
			FLOAT,
			FLOAT_VEC2,
			FLOAT_VEC3,
			FLOAT_VEC4,
			INT,
			BOOL,
			FLOAT_MAT3,
			FLOAT_MAT4
		};
		static UniformType mapGLToUniformType(unsigned int glenum);
		ShaderUniform(const std::string& name, UniformType type);
		bool isDirty();	
		virtual void synGL() = 0;

		virtual bool set(bool value);
		virtual bool set(int value);
		virtual bool set(float value);
		virtual bool set(Vector2f value);
		virtual bool set(Vector3f value);
		virtual bool set(Vector4f value);
		virtual bool set(Matrix3f value);
		virtual bool set(Matrix4f value);

		virtual bool get(bool& value);
		virtual bool get(int& value);
		virtual bool get(float& value);
		virtual bool get(Vector2f& value);
		virtual bool get(Vector3f& value);
		virtual bool get(Vector4f& value);
		virtual bool get(Matrix3f& value);
		virtual bool get(Matrix4f& value);

	protected:
		UniformType myType;
		int myLocation;
		const std::string& myName;
		bool myIsDirty;
	};


	class ShaderUniformBool : public ShaderUniform
	{
	public:
		ShaderUniformBool(const std::string& name);
		bool set(bool value);
		bool get(bool& value);
		void synGL();
	protected:
		bool myValue;
	};

	class ShaderUniformInt : public ShaderUniform
	{
	public:
		ShaderUniformInt(const std::string& name);
		bool set(int value);
		bool get(int& value);
		void synGL();
	protected:
		int myValue;
	};

	class ShaderUniformFloat : public ShaderUniform
	{
	public:
		ShaderUniformFloat(const std::string& name);
		bool set(float value);
		bool get(float& value);
		void synGL();
	protected:
		float myValue;
	};

	class ShaderUniformVec2f : public ShaderUniform
	{
	public:
		ShaderUniformVec2f(const std::string& name);
		bool set(Vector2f value);
		bool get(Vector2f& value);
		void synGL();
	protected:
		Vector2f myValue;
	};

	class ShaderUniformVec3f : public ShaderUniform
	{
	public:
		ShaderUniformVec3f(const std::string& name);
		bool set(Vector3f value);
		bool get(Vector3f& value);
		void synGL();
	protected:
		Vector3f myValue;
	};

	class ShaderUniformVec4f : public ShaderUniform
	{
	public:
		ShaderUniformVec4f(const std::string& name);
		bool set(Vector4f value);
		bool get(Vector4f& value);
		void synGL();
	protected:
		Vector4f myValue;
	};

	class ShaderUniformMat3f : public ShaderUniform
	{
	public:
		ShaderUniformMat3f(const std::string& name);
		bool set(Matrix3f value);
		bool get(Matrix3f& value);
		void synGL();
	protected:
		Matrix3f myValue;
	};

	class ShaderUniformMat4f : public ShaderUniform
	{
	public:
		ShaderUniformMat4f(const std::string& name);
		bool set(Matrix4f value);
		bool get(Matrix4f& value);
		void synGL();
	protected:
		Matrix4f myValue;
	};

	class AutomaticUniform
	{
	public:
		AutomaticUniform(const std::string& name);
		virtual void synGL() = 0;
	protected:
		ShaderUniform* myUniform;
		const std::string& myName;
	};

	class AutomaticUniformFactory
	{
	public:
		AutomaticUniformFactory(const std::string& name);
		virtual AutomaticUniform* create() = 0;
	protected:
		const std::string& myName;
	};

	class CameraViewMatrixUniform : public AutomaticUniform
	{
	public:
		friend class CameraViewMatrixUniformFactory;
		virtual void synGL();
	protected:
		CameraViewMatrixUniform(const std::string& name);	
	};

	class CameraViewMatrixUniformFactory : public AutomaticUniformFactory
	{
	public:
		CameraViewMatrixUniformFactory();
		virtual AutomaticUniform* create();
	};

}
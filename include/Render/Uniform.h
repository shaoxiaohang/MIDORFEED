#pragma once

#include <string>
#include <Core/Vector2.h>
#include <Core/Vector3.h>
#include <Core/Vector4.h>
#include <Core/Matrix3.h>
#include <Core/Matrix4.h>
#include <map>
namespace vrv
{
	class Program;
	class Scene;
	class Uniform
	{
	public:
		enum UniformType
		{
			FLOAT,
			FLOAT_VEC2,
			FLOAT_VEC3,
			FLOAT_VEC4,
			UNSIGNED_INT,
			INT,
			BOOL,
			FLOAT_MAT3,
			FLOAT_MAT4,
			SAMPLER_2D,
			SAMPLER_CUBE
		};
		static UniformType mapGLToUniformType(unsigned int glenum);
		Uniform();
		Uniform(const std::string& name, UniformType type, int location);
		bool isDirty();	
		virtual void synGL();
		int location();
		int size();

		virtual void* dataPointer() = 0;

		virtual bool set(bool value);
		virtual bool set(unsigned int value);
		virtual bool set(int value);
		virtual bool set(float value);
		virtual bool set(Vector2f value);
		virtual bool set(Vector3f value);
		virtual bool set(Vector4f value);
		virtual bool set(Matrix3f value);
		virtual bool set(Matrix4f value);

		virtual bool get(bool& value);
		virtual bool get(unsigned int& value);
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
		std::string myName;
		bool myIsDirty;
	};


	class UniformBool : public Uniform
	{
	public:
		UniformBool(const std::string& name, int location);
		bool set(bool value);
		bool get(bool& value);
		void synGL();
		void* dataPointer();
	protected:
		bool myValue;
	};

	class UniformInt : public Uniform
	{
	public:
		UniformInt(const std::string& name, int location);
		bool set(int value);
		bool get(int& value);
		void synGL();
		void* dataPointer();
	protected:
		int myValue;
	};

	class UniformUnsignedInt : public Uniform
	{
	public:
		UniformUnsignedInt(const std::string& name, int location);
		bool set(unsigned int value);
		bool get(unsigned int& value);
		void synGL();
		void* dataPointer();
	protected:
		unsigned int myValue;
	};

	class UniformFloat : public Uniform
	{
	public:
		UniformFloat(const std::string& name, int location);
		bool set(float value);
		bool get(float& value);
		void synGL();
		void* dataPointer();
	protected:
		float myValue;
	};

	class UniformVec2f : public Uniform
	{
	public:
		UniformVec2f(const std::string& name, int location);
		bool set(Vector2f value);
		bool get(Vector2f& value);
		void synGL();
		void* dataPointer();
	protected:
		Vector2f myValue;
	};

	class UniformVec3f : public Uniform
	{
	public:
		UniformVec3f(const std::string& name, int location);
		bool set(Vector3f value);
		bool get(Vector3f& value);
		void synGL();
		void* dataPointer();
	protected:
		Vector3f myValue;
	};

	class UniformVec4f : public Uniform
	{
	public:
		UniformVec4f(const std::string& name, int location);
		bool set(Vector4f value);
		bool get(Vector4f& value);
		void synGL();
		void* dataPointer();
	protected:
		Vector4f myValue;
	};

	class UniformMat3f : public Uniform
	{
	public:
		UniformMat3f(const std::string& name, int location);
		bool set(Matrix3f value);
		bool get(Matrix3f& value);
		void synGL();
		void* dataPointer();
	protected:
		Matrix3f myValue;
	};

	class UniformMat4f : public Uniform
	{
	public:
		UniformMat4f(const std::string& name, int location);
		bool set(Matrix4f value);
		bool get(Matrix4f& value);
		void synGL();
		void* dataPointer();
	protected:
		Matrix4f myValue;
	};

	class AutomaticUniform
	{
	public:
		AutomaticUniform();
		virtual void update() = 0;
		Uniform* uniform();
	protected:
		Uniform* myUniform;
	};

	class AutomaticUniformFactory
	{
	public:
		AutomaticUniformFactory(const std::string& name);
		virtual AutomaticUniform* create() = 0;
	protected:
		std::string myName;
	};

	class CameraViewMatrixUniform : public AutomaticUniform
	{
	public:
		friend class CameraViewMatrixUniformFactory;
		virtual void update();
	protected:
		CameraViewMatrixUniform(const std::string& name);
	};

	class CameraViewMatrixUniformFactory : public AutomaticUniformFactory
	{
	public:
		CameraViewMatrixUniformFactory();
		virtual AutomaticUniform* create();
	};

	class CameraPositionUniform : public AutomaticUniform
	{
	public:
		friend class CameraPositionUniformFactory;
		virtual void update();
	protected:
		CameraPositionUniform(const std::string& name);
	};

	class CameraPositionUniformFactory : public AutomaticUniformFactory
	{
	public:
		CameraPositionUniformFactory();
		virtual AutomaticUniform* create();
	};

	class CameraProjMatrixUniform : public AutomaticUniform
	{
	public:
		friend class CameraProjMatrixUniformFactory;
		virtual void update();
	protected:
		CameraProjMatrixUniform(const std::string& name);
	};

	class CameraProjMatrixUniformFactory : public AutomaticUniformFactory
	{
	public:
		CameraProjMatrixUniformFactory();
		virtual AutomaticUniform* create();
	};

}
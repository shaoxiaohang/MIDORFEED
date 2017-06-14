#pragma once

#include <string>
#include <Core/Vector2.h>
#include <Core/Vector3.h>
#include <Core/Vector4.h>
#include <Core/Matrix3.h>
#include <Core/Matrix4.h>
namespace vrv
{
	class Program;
	class Scene;
	class RenderInfo;
	class Uniform
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
			FLOAT_MAT4,
			SAMPLER_2D
		};
		static UniformType mapGLToUniformType(unsigned int glenum);
		Uniform();
		Uniform(const std::string& name, UniformType type, int location);
		bool isDirty();	
		virtual void synGL();
		int location();

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
	protected:
		int myValue;
	};

	class UniformFloat : public Uniform
	{
	public:
		UniformFloat(const std::string& name, int location);
		bool set(float value);
		bool get(float& value);
		void synGL();
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
	protected:
		Matrix4f myValue;
	};

	class AutomaticUniform
	{
	public:
		AutomaticUniform(Uniform* uniform);
		virtual void synGL(Scene* scene, RenderInfo& info) = 0;
	protected:
		Uniform* myUniform;
	};

	class AutomaticUniformFactory
	{
	public:
		AutomaticUniformFactory(const std::string& name);
		virtual AutomaticUniform* create(Uniform* uniform) = 0;
	protected:
		const std::string& myName;
	};

	class ModelMatrixUniform : public AutomaticUniform
	{
	public:
		friend class ModelMatrixUniformFactory;
		virtual void synGL(Scene* scene, RenderInfo& info);
	protected:
		ModelMatrixUniform(Uniform* uniform);
	};

	class ModelMatrixUniformFactory : public AutomaticUniformFactory
	{
	public:
		ModelMatrixUniformFactory();
		virtual AutomaticUniform* create(Uniform* uniform);
	};

	class UseDiffuseColorUniform : public AutomaticUniform
	{
	public:
		friend class UseDiffuseColorUniformFactory;
		virtual void synGL(Scene* scene, RenderInfo& info);
	protected:
		UseDiffuseColorUniform(Uniform* uniform);
	};

	class UseDiffuseColorUniformFactory : public AutomaticUniformFactory
	{
	public:
		UseDiffuseColorUniformFactory();
		virtual AutomaticUniform* create(Uniform* uniform);
	};

	class DiffuseColorUniform : public AutomaticUniform
	{
	public:
		friend class DiffuseColorUniformFactory;
		virtual void synGL(Scene* scene, RenderInfo& info);
	protected:
		DiffuseColorUniform(Uniform* uniform);
	};

	class DiffuseColorUniformFactory : public AutomaticUniformFactory
	{
	public:
		DiffuseColorUniformFactory();
		virtual AutomaticUniform* create(Uniform* uniform);
	};

	class CameraViewMatrixUniform : public AutomaticUniform
	{
	public:
		friend class CameraViewMatrixUniformFactory;
		virtual void synGL(Scene* scene, RenderInfo& info);
	protected:
		CameraViewMatrixUniform(Uniform* uniform);
	};

	class CameraViewMatrixUniformFactory : public AutomaticUniformFactory
	{
	public:
		CameraViewMatrixUniformFactory();
		virtual AutomaticUniform* create(Uniform* uniform);
	};

	class CameraProjMatrixUniform : public AutomaticUniform
	{
	public:
		friend class CameraProjMatrixUniformFactory;
		virtual void synGL(Scene* scene, RenderInfo& info);
	protected:
		CameraProjMatrixUniform(Uniform* uniform);
	};

	class CameraProjMatrixUniformFactory : public AutomaticUniformFactory
	{
	public:
		CameraProjMatrixUniformFactory();
		virtual AutomaticUniform* create(Uniform* uniform);
	};

	class AmbientColorUniform : public AutomaticUniform
	{
	public:
		friend class AmbientColorUniformFactory;
		virtual void synGL(Scene* scene, RenderInfo& info);
	protected:
		AmbientColorUniform(Uniform* uniform);
	};

	class AmbientColorUniformFactory : public AutomaticUniformFactory
	{
	public:
		AmbientColorUniformFactory();
		virtual AutomaticUniform* create(Uniform* uniform);
	};
}
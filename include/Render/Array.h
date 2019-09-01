#pragma once
#include<vector>
#include<Core/Vector2f.h>
#include<Core/Vector3f.h>
#include<Core/Vector4f.h>
#include<Core/Matrix3f.h>
#include<Core/Matrix4f.h>
namespace vrv
{
	class Array
	{
	public:
		enum DataType
		{
			INT,
			UNSIGNED_INT,
			FLOAT,
			VEC2F,
			VEC3F,
			VEC4F,
			MAT3F,
			MAT4F
		};
		Array(DataType type);
		Array(DataType type, int size);

		unsigned int size() const;

		unsigned int sizeInBytes();

		virtual const void* dataPointer() const = 0;
		virtual void resize(int size) = 0;

		virtual void initialize();

		DataType dataType();

		virtual void add(int);
		virtual void add(unsigned int);
		virtual void add(float);
		virtual void add(Vector2f);
		virtual void add(Vector3f);
		virtual void add(Vector4f);
		virtual void add(Matrix3f);
		virtual void add(Matrix4f);

		virtual void set(int index,int);
		virtual void set(int index, unsigned int);
		virtual void set(int index, float);
		virtual void set(int index, Vector2f);
		virtual void set(int index, Vector3f);
		virtual void set(int index, Vector4f);
		virtual void set(int index, Matrix3f);
		virtual void set(int index, Matrix4f);

	protected:
		virtual void calculateSize() = 0;

	protected:
		DataType myDataType;
		unsigned int mySize;
		unsigned int mySizeInBytes;
		bool myPreAllocated;
	};

	class ArrayInt : public Array
	{
	public:
		ArrayInt();

		ArrayInt(int size);

		virtual const void* dataPointer() const;

		int& operator[](unsigned int i);

		int get(unsigned int i);

		virtual void add(int);

		virtual void set(int, int);

		virtual void resize(int size);

	protected:
		virtual void calculateSize();

	protected:
		std::vector<int> myData;
	};

	class ArrayUnsignedInt : public Array
	{
	public:
		ArrayUnsignedInt();

		ArrayUnsignedInt(int size);

		ArrayUnsignedInt(ArrayUnsignedInt*);

		virtual const void* dataPointer() const;

		unsigned int& operator[](unsigned int i);

		unsigned int get(unsigned int i);

		virtual void add(unsigned int);

		virtual void set(int, unsigned int);

		virtual void resize(int size);

	protected:
		virtual void calculateSize();

	protected:
		std::vector<unsigned int> myData;
	};

	class ArrayFloat : public Array
	{
	public:
		ArrayFloat();

		ArrayFloat(int size);

		virtual const void* dataPointer() const;

		float& operator[](unsigned int i);

		float get(unsigned int i);

		virtual void add(float);

		virtual void set(int index, float);

		virtual void resize(int size);

	protected:
		virtual void calculateSize();

	protected:
		std::vector<float> myData;
	};

	class ArrayVec2 : public Array
	{
	public:
		ArrayVec2();

		ArrayVec2(int size);

		ArrayVec2(ArrayVec2*);

		virtual const void* dataPointer() const;

		Vector2f& operator[](unsigned int i);

		Vector2f get(unsigned int i);

		virtual void add(Vector2f);

		virtual void set(int index, Vector2f);

		virtual void resize(int size);

	protected:
		virtual void calculateSize();

	protected:
		std::vector<Vector2f> myData;
	};

	class ArrayVec3 : public Array
	{
	public:
		ArrayVec3();

		ArrayVec3(int size);

		ArrayVec3(ArrayVec3*);

		ArrayVec3(ArrayVec2*);

		virtual const void* dataPointer() const;

		Vector3f& operator[](unsigned int i);

		Vector3f get(unsigned int i);

		virtual void add(Vector3f);

		virtual void set(int index, Vector3f);

		virtual void resize(int size);

	protected:
		virtual void calculateSize();

	protected:
		std::vector<Vector3f> myData;
	};

	class ArrayVec4 : public Array
	{
	public:
		ArrayVec4();

		ArrayVec4(int size);

		virtual const void* dataPointer() const;

		Vector4f& operator[](unsigned int i);

		Vector4f get(unsigned int i);

		virtual void add(Vector4f);

		virtual void set(int index, Vector4f);

		virtual void resize(int size);

	protected:
		virtual void calculateSize();

	protected:
		std::vector<Vector4f> myData;
	};

	class ArrayMat3 : public Array
	{
	public:

		ArrayMat3();

		ArrayMat3(int size);

		virtual const void* dataPointer() const;

		Matrix3f& operator[](unsigned int i);

		Matrix3f get(unsigned int i);

		virtual void add(Matrix3f);

		virtual void set(int index, Matrix3f);

		virtual void resize(int size);

	protected:
		virtual void calculateSize();
	protected:
		std::vector<Matrix3f> myData;
	};

	class ArrayMat4 : public Array
	{
	public:

		ArrayMat4();

		ArrayMat4(int size);

		virtual const void* dataPointer() const;

		Matrix4f& operator[](unsigned int i);

		Matrix4f get(unsigned int i);

		virtual void add(Matrix4f);

		virtual void set(int index, Matrix4f);

		virtual void resize(int size);

	protected:

		virtual void calculateSize();

	protected:
		std::vector<Matrix4f> myData;
	};

}
#pragma once
#include<vector>
#include<Core/Vector2.h>
#include<Core/Vector3.h>
#include<Core/Vector4.h>
#include<Core/Matrix3.h>
#include<Core/Matrix4.h>
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
		Array(DataType type,unsigned int size);
		unsigned int size() const;
		unsigned int sizeInBytes() const;
		virtual const void* dataPointer() const = 0;
		DataType dataType();
	protected:
		DataType myDataType;
		unsigned int mySize;
		unsigned int mySizeInBytes;
		int myBaseTypeCount;
		unsigned int myGLBaseType;
	};

	class ArrayInt : public Array
	{
	public:
		ArrayInt(unsigned int size);
		virtual const void* dataPointer() const;
		int& operator[](unsigned int i);
	protected:
		std::vector<int> myData;
	};

	class ArrayUnsignedInt : public Array
	{
	public:
		ArrayUnsignedInt(unsigned int size);
		virtual const void* dataPointer() const;
		unsigned int& operator[](unsigned int i);
	protected:
		std::vector<unsigned int> myData;
	};

	class ArrayFloat : public Array
	{
	public:
		ArrayFloat(unsigned int size);
		virtual const void* dataPointer() const;
		float& operator[](unsigned int i);
	protected:
		std::vector<float> myData;
	};

	class ArrayVec2 : public Array
	{
	public:
		ArrayVec2(unsigned int size);
		virtual const void* dataPointer() const;
		Vector2f& operator[](unsigned int i);
	protected:
		std::vector<Vector2f> myData;
	};

	class ArrayVec3 : public Array
	{
	public:
		ArrayVec3(unsigned int size);
		virtual const void* dataPointer() const;
		Vector3f& operator[](unsigned int i);
	protected:
		std::vector<Vector3f> myData;
	};

	class ArrayVec4 : public Array
	{
	public:
		ArrayVec4(unsigned int size);
		virtual const void* dataPointer() const;
		Vector4f& operator[](unsigned int i);
	protected:
		std::vector<Vector4f> myData;
	};

	class ArrayMat3 : public Array
	{
	public:
		ArrayMat3(unsigned int size);
		virtual const void* dataPointer() const;
		Matrix3f& operator[](unsigned int i);
	protected:
		std::vector<Matrix3f> myData;
	};

	class ArrayMat4 : public Array
	{
	public:
		ArrayMat4(unsigned int size);
		virtual const void* dataPointer() const;
		Matrix4f& operator[](unsigned int i);
	protected:
		std::vector<Matrix4f> myData;
	};

}
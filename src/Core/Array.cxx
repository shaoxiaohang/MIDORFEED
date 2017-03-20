#include <Core/Array.h>
#include <GL/glew.h>
namespace vrv
{
	Array::Array(DataType type, unsigned int size)
		: myDataType(type)
		, mySize(size)
	{
		GLenum glType;
		switch (myDataType)
		{
		case vrv::Array::INT:
			glType = GL_INT;
			myBaseTypeCount = 1;
			mySizeInBytes = mySize*myBaseTypeCount*sizeof(int);
			break;
		case vrv::Array::FLOAT:
			glType = GL_FLOAT;
			myBaseTypeCount = 1;
			mySizeInBytes = mySize*myBaseTypeCount*sizeof(float);
			break;
		case vrv::Array::VEC2F:
			glType = GL_FLOAT;
			myBaseTypeCount = 2;
			mySizeInBytes = mySize*myBaseTypeCount*sizeof(float);
			break;
		case vrv::Array::VEC3F:
			glType = GL_FLOAT;
			myBaseTypeCount = 3;
			mySizeInBytes = mySize*myBaseTypeCount*sizeof(float);
			break;
		case vrv::Array::VEC4F:
			glType = GL_FLOAT;
			myBaseTypeCount = 4;
			mySizeInBytes = mySize*myBaseTypeCount*sizeof(float);
			break;
		case vrv::Array::MAT3F:
			glType = GL_FLOAT;
			myBaseTypeCount = 9;
			mySizeInBytes = mySize*myBaseTypeCount*sizeof(float);
			break;
		case vrv::Array::MAT4F:
			glType = GL_FLOAT;
			myBaseTypeCount = 16;
			mySizeInBytes = mySize*myBaseTypeCount*sizeof(float);
			break;
		default:
			break;
		}
	}

	unsigned int Array::size() const
	{
		return mySize;
	}
	unsigned int Array::sizeInBytes() const
	{
		return mySizeInBytes;
	}

	ArrayInt::ArrayInt(unsigned int size)
		: Array(Array::INT,size)
	{
		myData.resize(size);
	}

	const void* ArrayInt::dataPointer() const
	{
		return &myData[0];
	}

	int& ArrayInt::operator[](unsigned int i)
	{
		return myData[i];
	}

	ArrayFloat::ArrayFloat(unsigned int size)
		: Array(Array::FLOAT, size)
	{
		myData.resize(size);
	}

	const void* ArrayFloat::dataPointer() const
	{
		return &myData[0];
	}

	float& ArrayFloat::operator[](unsigned int i)
	{
		return myData[i];
	}

	ArrayVec2::ArrayVec2(unsigned int size)
		: Array(Array::VEC2F, size)
	{
		myData.resize(size);
	}

	const void* ArrayVec2::dataPointer() const
	{
		return &myData[0];
	}

	Vector2f& ArrayVec2::operator[](unsigned int i)
	{
		return myData[i];
	}

	ArrayVec3::ArrayVec3(unsigned int size)
		: Array(Array::VEC3F, size)
	{
		myData.resize(size);
	}

	const void* ArrayVec3::dataPointer() const
	{
		return &myData[0];
	}

	Vector3f& ArrayVec3::operator[](unsigned int i)
	{
		return myData[i];
	}

	ArrayVec4::ArrayVec4(unsigned int size)
		: Array(Array::VEC4F, size)
	{
		myData.resize(size);
	}

	const void* ArrayVec4::dataPointer() const
	{
		return &myData[0];
	}

	Vector4f& ArrayVec4::operator[](unsigned int i)
	{
		return myData[i];
	}

	ArrayMat3::ArrayMat3(unsigned int size)
		: Array(Array::MAT3F, size)
	{
		myData.resize(size);
	}

	const void* ArrayMat3::dataPointer() const
	{
		return &myData[0];
	}

	Matrix3f& ArrayMat3::operator[](unsigned int i)
	{
		return myData[i];
	}

	ArrayMat4::ArrayMat4(unsigned int size)
		: Array(Array::MAT4F, size)
	{
		myData.resize(size);
	}

	const void* ArrayMat4::dataPointer() const
	{
		return &myData[0];
	}

	Matrix4f& ArrayMat4::operator[](unsigned int i)
	{
		return myData[i];
	}

}
#include <Render/Array.h>
#include <Render/QtContext.h>
namespace vrv
{
	Array::Array(DataType type)
	{
		initialize(false);
	}

	Array::Array(DataType type, unsigned int size)
		: myDataType(type)
		, mySize(size)
	{
		initialize(true);
	}

	void Array::setSize(int size)
	{
		mySize = size;
		calculateSizeInBytes();
	}

	void Array::calculateSizeInBytes()
	{
		switch (myDataType)
		{
		case vrv::Array::INT:
			mySizeInBytes = mySize*myBaseTypeCount*sizeof(int);
			break;
		case vrv::Array::UNSIGNED_INT:
			mySizeInBytes = mySize*myBaseTypeCount*sizeof(unsigned int);
			break;
		case vrv::Array::FLOAT:
			mySizeInBytes = mySize*myBaseTypeCount*sizeof(float);
			break;
		case vrv::Array::VEC2F:
			mySizeInBytes = mySize*myBaseTypeCount*sizeof(float);
			break;
		case vrv::Array::VEC3F:
			mySizeInBytes = mySize*myBaseTypeCount*sizeof(float);
			break;
		case vrv::Array::VEC4F:
			mySizeInBytes = mySize*myBaseTypeCount*sizeof(float);
			break;
		case vrv::Array::MAT3F:
			mySizeInBytes = mySize*myBaseTypeCount*sizeof(float);
			break;
		case vrv::Array::MAT4F:
			mySizeInBytes = mySize*myBaseTypeCount*sizeof(float);
			break;
		default:
			break;
		}
	}

	void Array::initialize(bool knownSize)
	{
		GLenum glType;
		switch (myDataType)
		{
		case vrv::Array::INT:
			glType = GL_INT;
			myBaseTypeCount = 1;
			if (knownSize)
			{
				mySizeInBytes = mySize*myBaseTypeCount*sizeof(int);
			}
			break;
		case vrv::Array::UNSIGNED_INT:
			glType = GL_UNSIGNED_INT;
			myBaseTypeCount = 1;
			if (knownSize)
			{
				mySizeInBytes = mySize*myBaseTypeCount*sizeof(unsigned int);
			}
			break;
		case vrv::Array::FLOAT:
			glType = GL_FLOAT;
			myBaseTypeCount = 1;
			if (knownSize)
			{
				mySizeInBytes = mySize*myBaseTypeCount*sizeof(float);
			}
			break;
		case vrv::Array::VEC2F:
			glType = GL_FLOAT;
			myBaseTypeCount = 2;
			if (knownSize)
			{
				mySizeInBytes = mySize*myBaseTypeCount*sizeof(float);
			}
			break;
		case vrv::Array::VEC3F:
			glType = GL_FLOAT;
			myBaseTypeCount = 3;
			if (knownSize)
			{
				mySizeInBytes = mySize*myBaseTypeCount*sizeof(float);
			}
			break;
		case vrv::Array::VEC4F:
			glType = GL_FLOAT;
			myBaseTypeCount = 4;
			if (knownSize)
			{
				mySizeInBytes = mySize*myBaseTypeCount*sizeof(float);
			}
			break;
		case vrv::Array::MAT3F:
			glType = GL_FLOAT;
			myBaseTypeCount = 9;
			if (knownSize)
			{
				mySizeInBytes = mySize*myBaseTypeCount*sizeof(float);
			}
			break;
		case vrv::Array::MAT4F:
			glType = GL_FLOAT;
			myBaseTypeCount = 16;
			if (knownSize)
			{
				mySizeInBytes = mySize*myBaseTypeCount*sizeof(float);
			}
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

	Array::DataType Array::dataType()
	{
		return myDataType;
	}

	ArrayInt::ArrayInt(unsigned int size)
		: Array(Array::INT, size)
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

	ArrayUnsignedInt::ArrayUnsignedInt(unsigned int size)
		: Array(Array::UNSIGNED_INT, size)
	{
		myData.resize(size);
	}

	const void* ArrayUnsignedInt::dataPointer() const
	{
		return &myData[0];
	}

	unsigned int& ArrayUnsignedInt::operator[](unsigned int i)
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
#include <Render/Array.h>
#include <Render/QtContext.h>
namespace vrv
{
	Array::Array(DataType type)
		: myPreAllocated(false)
		, myDataType(type)
	{}

	Array::Array(DataType type, int size)
		: myPreAllocated(true)
		, myDataType(type)
	{
		mySize = size;
		initialize();
	}

	void Array::initialize()
	{
		switch (myDataType)
		{
		case vrv::Array::INT:
			mySizeInBytes = mySize*sizeof(int);
			break;
		case vrv::Array::UNSIGNED_INT:
			mySizeInBytes = mySize*sizeof(unsigned int);
			break;
		case vrv::Array::FLOAT:
			mySizeInBytes = mySize*sizeof(float);
			break;
		case vrv::Array::VEC2F:
			mySizeInBytes = mySize * 2 * sizeof(float);
			break;
		case vrv::Array::VEC3F:
			mySizeInBytes = mySize * 3 * sizeof(float);
			break;
		case vrv::Array::VEC4F:
			mySizeInBytes = mySize * 4 * sizeof(float);
			break;
		case vrv::Array::MAT3F:
			mySizeInBytes = mySize * 9 * sizeof(float);
			break;
		case vrv::Array::MAT4F:
			mySizeInBytes = mySize * 16 * sizeof(float);
			break;
		default:
			break;
		}
	}

	unsigned int Array::size() const
	{
		return mySize;
	}

	unsigned int Array::sizeInBytes()
	{
		if (!myPreAllocated)
		{
			calculateSize();
			initialize();
			myPreAllocated = true;
		}
	
		return mySizeInBytes;
	}

	void Array::add(int&)
	{}
	void Array::add(unsigned int&)
	{}
	void Array::add(float&)
	{}
	void Array::add(Vector2f&)
	{}
	void Array::add(Vector3f&)
	{}
	void Array::add(Vector4f&)
	{}
	void Array::add(Matrix3f&)
	{}
	void Array::add(Matrix4f&)
	{}

	Array::DataType Array::dataType()
	{
		return myDataType;
	}

	ArrayInt::ArrayInt()
		: Array(Array::INT)
	{
	}

	ArrayInt::ArrayInt(int size)
		: Array(Array::INT,size)
	{
		myData.resize(size);
	}

	void ArrayInt::add(int& value)
	{
		myData.push_back(value);
		mySize = myData.size();
	}

	void ArrayInt::calculateSize()
	{
		mySize = myData.size();
	}

	const void* ArrayInt::dataPointer() const
	{
		return &myData[0];
	}

	int& ArrayInt::operator[](unsigned int i)
	{
		return myData[i];
	}

	int ArrayInt::get(unsigned int i)
	{
		return myData[i];
	}

	ArrayUnsignedInt::ArrayUnsignedInt()
		: Array(Array::UNSIGNED_INT)
	{
	}

	ArrayUnsignedInt::ArrayUnsignedInt(int size)
		: Array(Array::UNSIGNED_INT, size)
	{
		myData.resize(size);
	}

	ArrayUnsignedInt::ArrayUnsignedInt(ArrayUnsignedInt* copy)
		: Array(Array::UNSIGNED_INT, copy->size())
	{
		myData.resize(mySize);
		for (unsigned int i = 0; i < mySize; ++i)
		{
			(*this)[i] = copy->get(i);
		}
	}

	void ArrayUnsignedInt::calculateSize()
	{
		mySize = myData.size();
	}

	const void* ArrayUnsignedInt::dataPointer() const
	{
		return &myData[0];
	}

	unsigned int& ArrayUnsignedInt::operator[](unsigned int i)
	{
		return myData[i];
	}

	unsigned int ArrayUnsignedInt::get(unsigned int i)
	{
		return myData[i];
	}

	void ArrayUnsignedInt::add(unsigned int& value)
	{
		myData.push_back(value);
		mySize = myData.size();
	}

	ArrayFloat::ArrayFloat()
		: Array(Array::FLOAT)
	{
	}

	ArrayFloat::ArrayFloat(int size)
		: Array(Array::FLOAT, size)
	{
		myData.resize(size);
	}

	void ArrayFloat::calculateSize()
	{
		mySize = myData.size();
	}

	const void* ArrayFloat::dataPointer() const
	{
		return &myData[0];
	}

	float& ArrayFloat::operator[](unsigned int i)
	{
		return myData[i];
	}

	float ArrayFloat::get(unsigned int i)
	{
		return myData[i];
	}

	void ArrayFloat::add(float& value)
	{
		myData.push_back(value);
		mySize = myData.size();
	}

	ArrayVec2::ArrayVec2()
		: Array(Array::VEC2F)
	{
	}

	ArrayVec2::ArrayVec2(int size)
		: Array(Array::VEC2F, size)
	{
		myData.resize(size);
	}

	ArrayVec2::ArrayVec2(ArrayVec2* copy)
		: Array(Array::VEC2F, copy->size())
	{
		myData.resize(mySize);
		for (unsigned int i = 0; i < mySize; ++i)
		{
			(*this)[i] = copy->get(i);
		}
	}

	void ArrayVec2::calculateSize()
	{
		mySize = myData.size();
	}

	const void* ArrayVec2::dataPointer() const
	{
		return &myData[0];
	}

	Vector2f& ArrayVec2::operator[](unsigned int i)
	{
		return myData[i];
	}

	Vector2f ArrayVec2::get(unsigned int i)
	{
		return myData[i];
	}

	void ArrayVec2::add(Vector2f& value)
	{
		myData.push_back(value);
		mySize = myData.size();
	}

	ArrayVec3::ArrayVec3()
		: Array(Array::VEC3F)
	{
	}

	ArrayVec3::ArrayVec3(int size)
		: Array(Array::VEC3F, size)
	{
		myData.resize(size);
	}

	ArrayVec3::ArrayVec3(ArrayVec2* copy)
		: Array(Array::VEC3F, copy->size())
	{
		myData.resize(mySize);
		for (unsigned int i = 0; i < mySize; ++i)
		{
			(*this)[i] = Vector3f(copy->get(i));
		}
	}

	ArrayVec3::ArrayVec3(ArrayVec3* copy)
		: Array(Array::VEC3F,copy->size())
	{
		myData.resize(mySize);
		for (unsigned int i = 0; i < mySize; ++i)
		{
			(*this)[i] = copy->get(i);
		}
	}

	void ArrayVec3::add(Vector3f& value)
	{
		myData.push_back(value);
		mySize = myData.size();
	}

	void ArrayVec3::calculateSize()
	{
		mySize = myData.size();
	}

	const void* ArrayVec3::dataPointer() const
	{
		return &myData[0];
	}

	Vector3f& ArrayVec3::operator[](unsigned int i)
	{
		return myData[i];
	}

	Vector3f ArrayVec3::get(unsigned int i)
	{
		return myData[i];
	}

	ArrayVec4::ArrayVec4()
		: Array(Array::VEC4F)
	{
	}

	ArrayVec4::ArrayVec4(int size)
		: Array(Array::VEC4F, size)
	{
		myData.resize(size);
	}

	void ArrayVec4::add(Vector4f& value)
	{
		myData.push_back(value);
		mySize = myData.size();
	}

	void ArrayVec4::calculateSize()
	{
		mySize = myData.size();
	}

	const void* ArrayVec4::dataPointer() const
	{
		return &myData[0];
	}

	Vector4f& ArrayVec4::operator[](unsigned int i)
	{
		return myData[i];
	}

	Vector4f ArrayVec4::get(unsigned int i)
	{
		return myData[i];
	}

	ArrayMat3::ArrayMat3()
		: Array(Array::MAT3F)
	{
	}

	ArrayMat3::ArrayMat3(int size)
		: Array(Array::MAT3F, size)
	{
		myData.resize(size);
	}

	void ArrayMat3::add(Matrix3f& value)
	{
		myData.push_back(value);
		mySize = myData.size();
	}

	const void* ArrayMat3::dataPointer() const
	{
		return &myData[0];
	}

	Matrix3f& ArrayMat3::operator[](unsigned int i)
	{
		return myData[i];
	}

	Matrix3f ArrayMat3::get(unsigned int i)
	{
		return myData[i];
	}

	void ArrayMat3::calculateSize()
	{
		mySize = myData.size();
	}

	ArrayMat4::ArrayMat4()
		: Array(Array::MAT4F)
	{
	}

	ArrayMat4::ArrayMat4(int size)
		: Array(Array::MAT4F, size)
	{
		myData.resize(size);
	}

	void ArrayMat4::add(Matrix4f& value)
	{
		myData.push_back(value);
		mySize = myData.size();
	}

	const void* ArrayMat4::dataPointer() const
	{
		return &myData[0];
	}

	void ArrayMat4::calculateSize()
	{
		mySize = myData.size();
	}

	Matrix4f& ArrayMat4::operator[](unsigned int i)
	{
		return myData[i];
	}

	Matrix4f ArrayMat4::get(unsigned int i)
	{
		return myData[i];
	}

}
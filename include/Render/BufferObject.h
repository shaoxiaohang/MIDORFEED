//#pragma once
//#include<vector>
//namespace vrv
//{
//	class Array;
//	class VertexAttribute;
//	class VertexArrayObject;
//	class BufferObject
//	{
//	public:
//		enum BufferTargetType
//		{
//			ARRAY_BUFFER,
//			ELEMENT_ARRAY_BUFFER
//		};
//
//		enum BufferUsage
//		{
//			STATIC_DRAW,
//			DYNAMIC_DRAW,
//			STREAM_DRAW
//		};
//
//		BufferObject(BufferTargetType type,BufferUsage usage = STATIC_DRAW);
//		~BufferObject();
//		virtual void copyFromSystemMemory(const Array* array);
//		virtual void bind() ;
//		virtual void unbind() ;
//	protected:
//		BufferTargetType myType;
//		BufferUsage myUsage;
//		unsigned int myGLUsage;
//		unsigned int myGLType;
//		unsigned int myID;
//	};
//
//
//}
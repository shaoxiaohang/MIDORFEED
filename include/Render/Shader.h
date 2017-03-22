//#pragma once
//#include <string>
//#include <vector>
//#include <map>
//namespace vrv
//{
//	class VertexAttribute;
//	class Shader
//	{
//	public:
//		typedef std::map<std::string, float> ConstantsMap;
//		typedef std::map<std::string, VertexAttribute*> VertexAttributesMap;
//
//		enum ShaderType
//		{
//			VertexShader,
//			FragmentShader
//		};
//
//		Shader(ShaderType type,const std::string& fileName);
//		void initialize();
//		void compile();
//		virtual void addVertexAttribute(VertexAttribute* attribute);
//		static bool checkCompileStatus(unsigned int id,std::string& error);
//		static void addUniformConstant(const std::string& name, float value);
//		const std::string name();
//		unsigned int ID();
//
//	protected:
//		unsigned int toGLEnum();
//
//	protected:
//		ShaderType myType;
//		unsigned int myID;
//		std::string mySource;
//		const std::string& myFileName;
//		bool myIsCompiled;
//		bool myInitialized;
//
//		VertexAttributesMap myVertexAttributesMap;
//
//		static bool myConstantsMapInitialized;
//		static ConstantsMap myConstansMap;
//	};
//}
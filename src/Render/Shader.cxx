//#include <Render/Shader.h>
//#include <Render/VertexAttribute.h>
//#include <Core/UsefulMarco.h>
//#include <fstream>
//#include <sstream>
//#include <GL/glew.h>
////#define SHADERFROMFILE 
//namespace vrv
//{
//	Shader::ConstantsMap Shader::myConstansMap;
//	bool Shader::myConstantsMapInitialized = false;
//
//	Shader::Shader(ShaderType type, const std::string& fileName)
//		: myType(type)
//		, myFileName(fileName)
//		, myInitialized(false)
//		, myIsCompiled(false)
//	{
//		if (!myConstantsMapInitialized)
//		{
//			addUniformConstant("vrv_pi", 3.14159265358979f);
//			addUniformConstant("vrv_oneOverPi", 0.318309886183791f);
//			addUniformConstant("vrv_twoPi", 6.28318530717959f);
//			addUniformConstant("vrv_halfPi", 1.5707963267949f);
//			myConstantsMapInitialized = true;
//		}
//#ifdef SHADERFROMFILE
//		std::ifstream shaderFile;
//		shaderFile.open(fileName.c_str());
//		if (shaderFile.fail())
//		{
//			VRV_ERROR("failt to open " + fileName);
//		}
//		std::stringstream shaderStream;
//		shaderStream << shaderFile.rdbuf();
//		shaderFile.close();
//		mySource = shaderStream.str();
//#else
//		if (myType == VertexShader)
//		{
//			mySource = "layout (location = 0) in vec3 pos;\nvoid main()\n{\ngl_Position = vec4(pos,1);\n}\n";
//		}
//		if (myType == FragmentShader)
//		{
//			mySource = "out vec4 color;\nvoid main()\n{\ncolor = vec4(1,0,0,1);\n}\n";
//		}
//#endif
//	}
//
//	void Shader::addVertexAttribute(VertexAttribute* attribute)
//	{
//		if (attribute)
//		{
//			if (myVertexAttributesMap.find(attribute->name()) == myVertexAttributesMap.end())
//			{
//				myVertexAttributesMap.insert(std::make_pair(attribute->name(), attribute));
//			}
//		}
//	}
//
//	void Shader::initialize()
//	{
//		if (!myInitialized)
//		{
//			myID = glCreateShader(toGLEnum());
//			std::size_t pos = mySource.find_first_of("\n\t");
//			const std::string& firstLine = mySource.substr(0, pos + 1);
//
//			bool hasGLVersionDefine = false;
//			if (firstLine.find("#version") != std::string::npos)
//			{
//				hasGLVersionDefine = true;
//				mySource = mySource.substr(pos + 1);
//			}
//
//			static const std::string version = "#version 330\n\n";
//			std::string finalString = version;
//			ConstantsMap::const_iterator itor1 = myConstansMap.begin();
//			for (; itor1 != myConstansMap.end(); ++itor1)
//			{
//				std::stringstream ss;
//				ss << "#define	" << itor1->first << "	" << itor1->second << std::endl;
//				finalString += ss.str();
//			}
//			VertexAttributesMap::const_iterator itor2 = myVertexAttributesMap.begin();
//			for (; itor2 != myVertexAttributesMap.end(); ++itor2)
//			{
//				std::stringstream ss;
//				ss << "in " << itor2->second->typeToGLSL() << " " << itor2->first << ";" << std::endl;
//				finalString += ss.str();
//			}
//
//			finalString += "\n";
//			finalString += mySource;
//#ifdef SHADERFROMFILE
//			std::ofstream os;
//			if (myType == VertexShader)
//			{
//				os.open("../userdata/output.vert");
//				os << finalString;
//				os.close();
//			}
//			else if (myType == FragmentShader)
//			{
//				os.open("../userdata/output.frag");
//				os << finalString;
//				os.close();
//			}
//#else
//			std::cout << finalString << std::endl;
//#endif
//			const GLchar* src = finalString.c_str();
//			glShaderSource(myID, 1, &src, 0);
//
//			myInitialized = true;
//		}
//
//	}
//
//	void Shader::compile()
//	{
//		if (!myIsCompiled)
//		{
//			glCompileShader(myID);
//			myIsCompiled = true;
//		}
//	}
//
//	bool Shader::checkCompileStatus(unsigned int id, std::string& error)
//	{
//		int res;
//		glGetShaderiv(id, GL_COMPILE_STATUS, &res);
//		if (res != GL_TRUE)
//		{
//			int infoLength = 0;
//			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLength);
//			char* str = new char[infoLength];
//			glGetShaderInfoLog(id, infoLength, 0, str);
//			error = str;
//			delete[] str;
//			return false;
//		}
//		return true;
//	}
//
//	void Shader::addUniformConstant(const std::string& name, float value)
//	{
//		if (myConstansMap.find(name) == myConstansMap.end())
//		{
//			myConstansMap.insert(std::make_pair(name, value));
//		}
//	}
//
//	const std::string Shader::name()
//	{
//		return myFileName;
//	}
//
//	unsigned int Shader::ID()
//	{
//		return myID;
//	}
//
//	unsigned int Shader::toGLEnum()
//	{
//		switch (myType)
//		{
//		case vrv::Shader::VertexShader:
//			return GL_VERTEX_SHADER;
//			break;
//		case vrv::Shader::FragmentShader:
//			return GL_FRAGMENT_SHADER;
//			break;
//		default:
//			break;
//		}
//	}
//}
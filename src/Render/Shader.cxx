#include <Render/Shader.h>
#include <Core/UsefulMarco.h>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
namespace vrv
{
	

	ShaderAttribute::ShaderAttribute(std::string name, unsigned int location)
		: myName(name)
		, myLocation(location)
	{}

	unsigned int ShaderAttribute::location()
	{
		return myLocation;
	}

	const std::string& ShaderAttribute::name()
	{
		return myName;
	}

	Shader::ConstantsMap Shader::myConstansMap;
	bool Shader::myConstantsMapInitialized = false;

	Shader::Shader(ShaderType type, const std::string& fileName)
		: myType(type)
		, myFileName(fileName)
		, myInitialized(false)
		, myIsCompiled(false)		
	{
		if (!myConstantsMapInitialized)
		{
			addShaderUniformConstant("vrv_pi", 3.14159265358979f);
			addShaderUniformConstant("vrv_oneOverPi", 0.318309886183791f);
			addShaderUniformConstant("vrv_twoPi", 6.28318530717959f);
			addShaderUniformConstant("vrv_halfPi", 1.5707963267949f);
			myConstantsMapInitialized = true;
		}
		//std::ifstream shaderFile;
		//shaderFile.open(fileName.c_str());
		//std::stringstream shaderStream;
		//shaderStream << shaderFile.rdbuf();
		//shaderFile.close();
		//mySource = shaderStream.str();

		mySource = "void main()\n{\n}\n";
	}

	void Shader::addVertexAttribute(ShaderAttribute* attribute)
	{
		if (attribute)
		{
			if (myVertexAttributesMap.find(attribute->name()) == myVertexAttributesMap.end())
			{
				myVertexAttributesMap.insert(std::make_pair(attribute->name(), attribute));
			}
		}
	}

	void Shader::initialize()
	{
		if (!myInitialized)
		{
			myID = glCreateShader(toGLEnum());
			std::size_t pos = mySource.find_first_of("\n\t");
			const std::string& firstLine = mySource.substr(0, pos + 1);

			bool hasGLVersionDefine = false;
			if (firstLine.find("#version") != std::string::npos)
			{
				hasGLVersionDefine = true;
				mySource = mySource.substr(pos + 1);
			}

			static const std::string version = "#version 330\n\n";
			std::string finalString = version;
			ConstantsMap::const_iterator itor1 = myConstansMap.begin();
			for (; itor1 != myConstansMap.end(); ++itor1)
			{
				std::stringstream ss;
				ss << "#define	" << itor1->first << "	" << itor1->second << std::endl;
				finalString += ss.str();
			}
			VertexAttributesMap::const_iterator itor2 = myVertexAttributesMap.begin();
			for (; itor2 != myVertexAttributesMap.end(); ++itor2)
			{
				std::stringstream ss;
				ss << "in " << itor2->second->typeToString() << " " << itor2->first << std::endl;
				finalString += ss.str();
			}
			
			finalString += "\n";
			finalString += mySource;
			const GLchar* src = finalString.c_str();
			glShaderSource(myID, 1, &src, 0);

			myInitialized = true;
		}
		
	}

	void Shader::compile()
	{
		if (!myIsCompiled)
		{
			glCompileShader(myID);
			myIsCompiled = true;
		}
	}

	bool Shader::checkCompileStatus(unsigned int id, std::string& error)
	{
		int res;
		glGetShaderiv(id, GL_COMPILE_STATUS, &res);
		if (res != GL_TRUE)
		{
			int infoLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLength);
			char* str = new char[infoLength];
			glGetShaderInfoLog(id, infoLength, 0, str);
			error = str;
			delete[] str;
			return false;
		}
		return true;
	}

	void Shader::addShaderUniformConstant(const std::string& name, float value)
	{
		if (myConstansMap.find(name) == myConstansMap.end())
		{
			myConstansMap.insert(std::make_pair(name, value));
		}
	}

	const std::string Shader::name()
	{
		return myFileName;
	}

	unsigned int Shader::ID()
	{
		return myID;
	}

	unsigned int Shader::toGLEnum()
	{
		switch (myType)
		{
		case vrv::Shader::VertexShader:
			return GL_VERTEX_SHADER;
			break;
		case vrv::Shader::FragmentShader:
			return GL_FRAGMENT_SHADER;
			break;
		default:
			break;
		}
	}
}
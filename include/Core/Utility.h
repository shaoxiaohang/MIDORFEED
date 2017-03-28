#pragma once
#include<iostream>
#include<string>
#include<algorithm>
namespace vrv
{
#define DISALLOW_COPY_AND_ASSIGN(ClassName)\
		ClassName(const ClassName&); \
		void operator=(const ClassName&);

#define VRV_ERROR(message)\
		std::cout <<__FILE__<<"  "<<__LINE__<<"  ERROR "<<__FUNCTION__<<"***"<<message<<"***"<< std::endl;

#define VRV_INFO(message)\
	std::cout <<"VRV INFO:  " << message<< std::endl;

#define MAXIMUM_TEXTURE_UNITS 16
	class Utility
	{
	public:
		static std::string getExtension(const std::string& fileName)
		{
			std::size_t p = fileName.find_last_of(".");
			if (p != fileName.npos)
			{
				return fileName.substr(p + 1);
			}
			else
			{
				return "";
			}		
		}

		static std::string getExtensionWithLowercase(const std::string& fileName)
		{
			std::size_t p = fileName.find_last_of(".");
			if (p != fileName.npos)
			{
				std::string ext = fileName.substr(p + 1);
				std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
				return ext;
			}
			else
			{
				return "";
			}
		}
	};
}
#pragma once
#include<iostream>
namespace vrv
{
#define DISALLOW_COPY_AND_ASSIGN(ClassName)\
		ClassName(const ClassName&); \
		void operator=(const ClassName&);

#define VRV_ERROR(message)\
		std::cout <<__FILE__<<"  "<<__LINE__<<"  ERROR "<<__FUNCTION__<<"***"<<message<<"***"<< std::endl;

#define VRV_INFO(message)\
	std::cout <<"VRV INFO:  " << message<< std::endl;
}
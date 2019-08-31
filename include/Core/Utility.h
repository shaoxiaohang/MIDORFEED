#pragma once
#include<iostream>
#include<string>
#include<algorithm>
#include<cmath>

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

		static std::string getBaseDirectory(const std::string& fileName)
		{
			std::size_t p = fileName.find_last_of('/');
			if (p != fileName.npos)
			{
				return fileName.substr(0, p+1);
			}
			else
			{
				return "";
			}
		}
		
		static float degreeToRadian(float degree)
		{
			return PI*degree / 180.0f;
		}

		static float tan(float degree)
		{
			return tanf(degreeToRadian(degree));
		}

		static float atan(float degree)
		{
			return atanf(degreeToRadian(degree));
		}

		static float atan2(float y, float x)
		{
			return atan2f(y,x);
		}

		static float sin(float degree)
		{
			return sinf(degreeToRadian(degree));
		}

		static float asin(float value)
		{
			return asinf(value);
		}

		static float acos(float value)
		{
			return acosf(value);
		}

		static float cos(float degree)
		{
			return cosf(degreeToRadian(degree));
		}

		static float sqrt(float value)
		{
			return sqrtf(value);
		}

		static float pow(float base, float exponent)
		{
			return powf(base, exponent);
		}

      static int powi(int base, int exponent)
      {
         return pow(base, exponent);
      }

		static double absd(double v)
		{
			return abs(v);
		}

		static float PI;
		static float twoPI;
	};
}
#pragma once
#include <Core/UsefulMarco.h>
#include <cassert>
namespace vrv
{
	template <typename T>
	class Singleton
	{
	public:

		Singleton()
		{
			if (myInstance)
			{
				VRV_ERROR("Singelton is already instanced")
			}
			myInstance = static_cast<T*>(this);
		}

		static T* instancePtr()
		{
			assert(myInstance);
			return myInstance;
		}
		static T& instance()
		{
			assert(myInstance);
			return *myInstance;
		}

	protected:

		static T* myInstance;

	private:
		DISALLOW_COPY_AND_ASSIGN(Singleton)
	};
}
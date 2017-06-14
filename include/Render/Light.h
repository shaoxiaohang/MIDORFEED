#pragma once
#include <Core/Vector3.h>
namespace vrv
{
	class Light
	{
	public:
		enum LightType
		{
			DirectionalLight,
			PointLight,
			SpotLight
		};

		Light();

		void setType();
		LightType type();
		void setPosition(Vector3f position);
		Vector3f position();
		void setDirection(Vector3f direction);
		Vector3f direction();

	protected:
		Vector3f myPosition;
		Vector3f myDirection;
		float myConstantTerm;
		float myLinearTerm;
		float myQuadraticTerm;
		float myCutoffAngle;
		float myFadeAngle;
		bool myIsDirty;
	};
}
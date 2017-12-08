#pragma once
#include <Core/Vector3.h>
#include <string>
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

		Light(const std::string& name);

		void setType(LightType type);
		LightType type();

		void setPosition(Vector3f position);
		Vector3f position();

		void setDirection(Vector3f direction);
		Vector3f direction();

		void setAmbient(Vector3f ambient);
		Vector3f ambient();

		void setDiffuse(Vector3f diffuse);
		Vector3f diffuse();

		void setSpecular(Vector3f specular);
		Vector3f specular();

		void setConstantTerm(float constant);
		float constantTerm();

		void setLinearTerm(float linear);
		float linearTerm();

		void setQuadraticTerm(float quadratic);
		float quadraticTerm();

		void setCutoffAngle(float cutoff);
		float cutoffAngle();

		void setFadeAngle(float fade);
		float fadeAngle();

		void setCastShadow(bool);
		bool castShadow();

	protected:
		LightType myType;
		Vector3f myPosition;
		Vector3f myDirection;
		Vector3f myAmbient;
		Vector3f myDiffuse;
		Vector3f mySpecular;
		float myConstantTerm;
		float myLinearTerm;
		float myQuadraticTerm;
		float myCutoffAngle;
		float myFadeAngle;
		std::string myName;
		bool myCastShadow;
	};
}
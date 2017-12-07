#include <Render/Light.h>

namespace vrv
{
	Light::Light(const std::string& name)
		: myConstantTerm(1.0)
		, myLinearTerm(0.045)
		, myQuadraticTerm(0.0075)
		, myName(name)
	{

	}

	void Light::setType(LightType type)
	{
		myType = type;
	}
	Light::LightType Light::type()
	{
		return myType;
	}

	void Light::setPosition(Vector3f position)
	{
		myPosition = position;
	}
	Vector3f Light::position()
	{
		return myPosition;
	}

	void Light::setDirection(Vector3f direction)
	{
		myDirection = direction;
	}
	Vector3f Light::direction()
	{
		return myDirection;
	}

	void Light::setAmbient(Vector3f ambient)
	{
		myAmbient = ambient;
	}
	Vector3f Light::ambient()
	{
		return myAmbient;
	}

	void Light::setDiffuse(Vector3f diffuse)
	{
		myDiffuse = diffuse;
	}
	Vector3f Light::diffuse()
	{
		return myDiffuse;
	}

	void Light::setSpecular(Vector3f specular)
	{
		mySpecular = specular;
	}
	Vector3f Light::specular()
	{
		return mySpecular;
	}

	void Light::setConstantTerm(float constant)
	{
		myConstantTerm = constant;
	}
	float Light::constantTerm()
	{
		return myConstantTerm;
	}

	void Light::setLinearTerm(float linear)
	{
		myLinearTerm = linear;
	}
	float Light::linearTerm()
	{
		return myLinearTerm;
	}

	void Light::setQuadraticTerm(float quadratic)
	{
		myQuadraticTerm = quadratic;
	}
	float Light::quadraticTerm()
	{
		return myQuadraticTerm;
	}

	void Light::setCutoffAngle(float cutoff)
	{
		myCutoffAngle = cutoff;
	}
	float Light::cutoffAngle()
	{
		return myCutoffAngle;
	}

	void Light::setFadeAngle(float fade)
	{
		myFadeAngle = fade;
	}
	float Light::fadeAngle()
	{
		return myFadeAngle;
	}
}
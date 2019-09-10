#pragma once

namespace vrv
{
	class Geodetic3D
	{
	public:
		Geodetic3D(float lon, float lat, float height);

		float longtitude();
		float lantitude();
		float height();

	protected:
		float myLongtitude;
		float myLantitude;
		float myHeight;
	};

	class Geodetic2D
	{
	public:
		Geodetic2D(float lon, float lat);

		float longtitude();
		float lantitude();

	protected:
		float myLongtitude;
		float myLantitude;
	};
	
}
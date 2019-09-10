#include <Render/Ellipsoid.h>
#include <Core/Utility.h>
#include <Render/Tessellation.h>
#include <Render/BoxTessellator.h>
#include <algorithm>
namespace vrv
{

	Ellipsoid::Ellipsoid(float a, float b, float c)
		: myXAxesLength(a)
		, myYAxesLength(b)
		, myZAxesLength(c)
	{	
		myMaximumRadius = std::max(std::max(a, b), c);
		myRadius = Vector3f(a, b, c);
		mySquareXAxes = a*a;
		mySquareYAxes = b*b;
		mySquareZAxes = c*c;
		myOneSquareXAxes = 1.0f / (a*a);
		myOneSquareYAxes = 1.0f / (b*b);
		myOneSquareZAxes = 1.0f / (c*c);

		myGeometry = BoxTessellator::compute(myRadius * 2);
	}

   float Ellipsoid::xAxes() const
	{
		return myXAxesLength;
	}

   float Ellipsoid::yAxes() const
	{
		return myYAxesLength;
	}

   float Ellipsoid::zAxes() const
	{
		return myZAxesLength;
	}

   float Ellipsoid::maximumRadius() const
	{
		return myMaximumRadius;
	}

	Vector3f Ellipsoid::radius() const
	{
		return myRadius;
	}

	Vector3f Ellipsoid::geodeticSurfaceNormal(Vector3f geocentric)
	{
		Vector3f normal = geocentric * Vector3f(myOneSquareXAxes, myOneSquareYAxes, myOneSquareZAxes);
		return normal.normalizedVector();
	}

	Vector3f Ellipsoid::geodeticSurfaceNormal(Geodetic3D point)
	{
		float longtitude = point.longtitude();
		float lantitude = point.lantitude();
		float cosLantitude = Utility::cos(lantitude);
		float cosLongtitude = Utility::cos(longtitude);
		float sinLantitude = Utility::sin(lantitude);
		float sinLongtitude = Utility::sin(longtitude);

		return Vector3f(cosLantitude*cosLongtitude, cosLantitude*sinLongtitude, sinLantitude);
	}

	Vector3f Ellipsoid::geodeticToGeocentric(Geodetic3D point)
	{
		Vector3f normal = geodeticSurfaceNormal(point);
      float squareA = myXAxesLength*myXAxesLength;
      float squareB = myYAxesLength*myYAxesLength;
      float squareC = myZAxesLength*myZAxesLength;
		
		Vector3f square = Vector3f(squareA, squareB, squareC);
		Vector3f squareNormal = normal*normal;
      float d = Utility::sqrt(squareNormal.dotProduct(square));

		Vector3f surface = Vector3f(normal.x() * squareA / d, normal.y()*squareB / d, normal.z()*squareC / d);

		return surface + normal*point.height();

	}

	Geodetic2D Ellipsoid::surfacePointToGeodetic2D(Vector3f geocentric)
	{
		Vector3f normal = geodeticSurfaceNormal(geocentric);
      float longtitude = Utility::atan2(normal.y(), normal.x());
      float lantitude = Utility::asin(normal.z() / normal.length());
		return Geodetic2D(longtitude, lantitude);
	}

	Vector3f Ellipsoid::scaleToGeocentricSurface(Vector3f geocentric)
	{
		Vector3f square = geocentric*geocentric;
      float beta = Utility::sqrt(1.0f / (square.dotProduct(Vector3f(myOneSquareXAxes, myOneSquareYAxes, myOneSquareZAxes))));
		return geocentric*beta;
	}

	Vector3f Ellipsoid::scaleToGeodeticSurface(Vector3f position)
	{
      float beta = 1.0f / Utility::sqrt(
			(position.x() * position.x()) * myOneSquareXAxes +
			(position.y() * position.y()) * myOneSquareYAxes +
			(position.z() * position.z()) * myOneSquareZAxes);
      float n = Vector3f(
			beta * position.x() * myOneSquareXAxes,
			beta * position.y() * myOneSquareYAxes,
         beta * position.z() * myOneSquareZAxes).length();
      float alpha = (1.0f - beta) * (position.length() / n);

      float x2 = position.x() * position.x();
      float y2 = position.y() * position.y();
      float z2 = position.z() * position.z();

      float da = 0.0f;
      float db = 0.0f;
      float dc = 0.0f;

      float s = 0.0;
      float dSdA = 1.0f;

		do
		{
			alpha -= (s / dSdA);

			da = 1.0f + (alpha * myOneSquareXAxes);
			db = 1.0f + (alpha * myOneSquareYAxes);
			dc = 1.0f + (alpha * myOneSquareZAxes);

         float da2 = da * da;
         float db2 = db * db;
         float dc2 = dc * dc;

         float da3 = da * da2;
         float db3 = db * db2;
         float dc3 = dc * dc2;

			s = x2 / (mySquareXAxes * da2) +
				y2 / (mySquareYAxes * db2) +
				z2 / (mySquareZAxes * dc2) - 1.0f;

			dSdA = -2.0f *
				(x2 / (mySquareXAxes*mySquareXAxes * da3) +
				y2 / (mySquareYAxes*mySquareYAxes * db3) +
				z2 / (mySquareZAxes*mySquareZAxes * dc3));
		} while (Utility::absd(s) > 1e-10);

		return Vector3f(
			position.x() / da,
			position.y() / db,
			position.z() / dc);
	}

	Geodetic3D Ellipsoid::geocentricToGeodetic(Vector3f geocentric)
	{
		Vector3f surfacePoint = scaleToGeodeticSurface(geocentric);
		Vector3f h = geocentric - surfacePoint;
		int sign = h.dotProduct(geocentric) > 0 ? 1:-1;
		Geodetic2D geodetic2D = surfacePointToGeodetic2D(surfacePoint);
      float height = sign * h.length();

		return Geodetic3D(geodetic2D.longtitude(), geodetic2D.lantitude(), height);
	}

	std::vector<Vector3f> Ellipsoid::computeCurve(Vector3f p, Vector3f q, float granularity)
	{
		std::vector<Vector3f> points;
		double angle = p.angelBetween(q);
		Vector3f planeNormal = q.crossProduct(q).normalizedVector();
		int num = (int)(angle / granularity) ;
		for (int i = 1; i <= num; ++i)
		{
			Vector3f point = p.rotateAroundAxis(planeNormal, i*granularity);
			Vector3f surface = scaleToGeocentricSurface(point);
			points.push_back(surface);
		}

		return points;
	}

   float Ellipsoid::height(Vector3f geocentric)
	{
		return geocentricToGeodetic(geocentric).height();
	}

	Geometry* Ellipsoid::geometry()
	{
		return myGeometry;
	}
}
#include <Render/Ellipsoid.h>
#include <Core/Utility.h>
#include <Render/Tessellation.h>
#include <Render/BoxTessellator.h>
#include <algorithm>
namespace vrv
{

	Ellipsoid::Ellipsoid(double a, double b, double c)
		: myXAxesLength(a)
		, myYAxesLength(b)
		, myZAxesLength(c)
	{	
		myMaximumRadius = std::max(std::max(a, b), c);
		myRadius = Vector3f(a, b, c);
		mySquareXAxes = a*a;
		mySquareYAxes = b*b;
		mySquareZAxes = c*c;
		myOneSquareXAxes = 1.0 / (a*a);
		myOneSquareYAxes = 1.0 / (b*b);
		myOneSquareZAxes = 1.0 / (c*c);

		myGeometry = BoxTessellator::compute(myRadius * 2);
	}

	double Ellipsoid::xAxes() const
	{
		return myXAxesLength;
	}

	double Ellipsoid::yAxes() const
	{
		return myYAxesLength;
	}

	double Ellipsoid::zAxes() const
	{
		return myZAxesLength;
	}

	double Ellipsoid::maximumRadius() const
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
		double squareA = myXAxesLength*myXAxesLength;
		double squareB = myYAxesLength*myYAxesLength;
		double squareC = myZAxesLength*myZAxesLength;
		
		Vector3f square = Vector3f(squareA, squareB, squareC);
		Vector3f squareNormal = normal*normal;
		double d = Utility::sqrt(squareNormal.dotProduct(square));

		Vector3f surface = Vector3f(normal.x() * squareA / d, normal.y()*squareB / d, normal.z()*squareC / d);

		return surface + normal*point.height();

	}

	Geodetic2D Ellipsoid::surfacePointToGeodetic2D(Vector3f geocentric)
	{
		Vector3f normal = geodeticSurfaceNormal(geocentric);
		double longtitude = Utility::atan2(normal.y(), normal.x());
		double lantitude = Utility::asin(normal.z() / normal.magnitude());
		return Geodetic2D(longtitude, lantitude);
	}

	Vector3f Ellipsoid::scaleToGeocentricSurface(Vector3f geocentric)
	{
		Vector3f square = geocentric*geocentric;
		double beta = Utility::sqrt(1.0 / (square.dotProduct(Vector3f(myOneSquareXAxes, myOneSquareYAxes, myOneSquareZAxes))));
		return geocentric*beta;
	}

	Vector3f Ellipsoid::scaleToGeodeticSurface(Vector3f position)
	{
		double beta = 1.0 / Utility::sqrt(
			(position.x() * position.x()) * myOneSquareXAxes +
			(position.y() * position.y()) * myOneSquareYAxes +
			(position.z() * position.z()) * myOneSquareZAxes);
		double n = Vector3f(
			beta * position.x() * myOneSquareXAxes,
			beta * position.y() * myOneSquareYAxes,
			beta * position.z() * myOneSquareZAxes).magnitude();
		double alpha = (1.0 - beta) * (position.magnitude() / n);

		double x2 = position.x() * position.x();
		double y2 = position.y() * position.y();
		double z2 = position.z() * position.z();

		double da = 0.0;
		double db = 0.0;
		double dc = 0.0;

		double s = 0.0;
		double dSdA = 1.0;

		do
		{
			alpha -= (s / dSdA);

			da = 1.0 + (alpha * myOneSquareXAxes);
			db = 1.0 + (alpha * myOneSquareYAxes);
			dc = 1.0 + (alpha * myOneSquareZAxes);

			double da2 = da * da;
			double db2 = db * db;
			double dc2 = dc * dc;

			double da3 = da * da2;
			double db3 = db * db2;
			double dc3 = dc * dc2;

			s = x2 / (mySquareXAxes * da2) +
				y2 / (mySquareYAxes * db2) +
				z2 / (mySquareZAxes * dc2) - 1.0;

			dSdA = -2.0 *
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
		double height = sign * h.magnitude();

		return Geodetic3D(geodetic2D.longtitude(), geodetic2D.lantitude(), height);
	}

	std::vector<Vector3f> Ellipsoid::computeCurve(Vector3f p, Vector3f q, double granularity)
	{
		std::vector<Vector3f> points;
		double angle = p.angelBetween(q);
		Vector3f planeNormal = q.crossProduct(q).normalizedVector();
		int num = angle / granularity ;
		for (int i = 1; i <= num; ++i)
		{
			Vector3f point = p.rotateAroundAxis(planeNormal, i*granularity);
			Vector3f surface = scaleToGeocentricSurface(point);
			points.push_back(surface);
		}

		return points;
	}

	double Ellipsoid::height(Vector3f geocentric)
	{
		return geocentricToGeodetic(geocentric).height();
	}

	Geometry* Ellipsoid::geometry()
	{
		return myGeometry;
	}
}
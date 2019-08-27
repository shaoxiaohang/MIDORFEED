#pragma once
#include <Core/Vector3.h>
#include <Core/Geodetic.h>
#include <vector>
namespace vrv
{
	class Geometry;
	class Ellipsoid
	{
	public:
		Ellipsoid(double x, double y, double z);

		double xAxes() const;
		double yAxes() const;
		double zAxes() const;

		Vector3f radius() const;
		double maximumRadius() const;

		//Gets the geodetic normal for a point on the ellipsoid.
		Vector3f geodeticSurfaceNormal(Vector3f geocentric);

		//Gets the geodetic normal for a point on the ellipsoid.
		Vector3f geodeticSurfaceNormal(Geodetic3D point);

		//Converts a geodetic point to geocentric
		Vector3f geodeticToGeocentric(Geodetic3D point);

		//Gets the geodetic coordinate from a point on the ellipsoid.
		Geodetic2D surfacePointToGeodetic2D(Vector3f geocentric);

		//Gets the point on the ellipsoid from an arbitary geocentric point.
		Vector3f scaleToGeocentricSurface(Vector3f geocentric);

		//FIXME dont understand this code
		Vector3f scaleToGeodeticSurface(Vector3f geocentric);

		Geodetic3D geocentricToGeodetic(Vector3f geocentric);

		std::vector<Vector3f> computeCurve(Vector3f p, Vector3f q, double granularity);

		double height(Vector3f geocentric);

		Geometry* geometry();

	protected:
		double myXAxesLength;
		double myYAxesLength;
		double myZAxesLength;
		double myMaximumRadius;
		Vector3f myRadius;
		double mySquareXAxes;
		double mySquareYAxes;
		double mySquareZAxes;
		double myOneSquareXAxes;
		double myOneSquareYAxes;
		double myOneSquareZAxes;
		bool myUseGPURayCasting;
		Geometry* myGeometry;
		
	};
}
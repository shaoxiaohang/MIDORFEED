#pragma once
#include <Core/Vector3f.h>
#include <Core/Geodetic.h>
#include <vector>
namespace vrv
{
	class Geometry;
	class Ellipsoid
	{
	public:
		Ellipsoid(float x, float y, float z);

      float xAxes() const;
      float yAxes() const;
      float zAxes() const;

		Vector3f radius() const;
      float maximumRadius() const;

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

		std::vector<Vector3f> computeCurve(Vector3f p, Vector3f q, float granularity);

      float height(Vector3f geocentric);

		Geometry* geometry();

	protected:
      float myXAxesLength;
      float myYAxesLength;
      float myZAxesLength;
      float myMaximumRadius;
		Vector3f myRadius;
      float mySquareXAxes;
      float mySquareYAxes;
      float mySquareZAxes;
      float myOneSquareXAxes;
      float myOneSquareYAxes;
      float myOneSquareZAxes;
		bool myUseGPURayCasting;
		Geometry* myGeometry;
		
	};
}
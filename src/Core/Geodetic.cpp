#include <Core/Geodetic.h>

namespace vrv
{
   Geodetic3D::Geodetic3D(float lon, float lat, float height)
      : myLongtitude(lon)
      , myLantitude(lat)
      , myHeight(height)
   {

   }

   float Geodetic3D::longtitude()
   {
      return myLongtitude;
   }

   float Geodetic3D::lantitude()
   {
      return myLantitude;
   }

   float Geodetic3D::height()
   {
      return myHeight;
   }

   Geodetic2D::Geodetic2D(float lon, float lat)
      : myLongtitude(lon)
      , myLantitude(lat)
   {

   }

   float Geodetic2D::longtitude()
   {
      return myLongtitude;
   }

   float Geodetic2D::lantitude()
   {
      return myLantitude;
   }
}
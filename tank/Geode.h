#ifndef GEODE_H_INCLUDED
#define GEODE_H_INCLUDED

#include <string>
#include <boost/smart_ptr.hpp>
#include "GeoSet.h"

typedef boost::shared_ptr<GeoSet> GeoSetPtr;

//: Defines a collection of GeoSets.
class Geode
{
public:
   //: Creates a new geode containing zero geosets with the name "".
   Geode();

   //: Adds the given geoset to this geode. The geoset is added to the end of
   //  the list of geosets. The geoset will be deleted when this geode is
   //  destroyed unless you maintained a safe_ptr to that geoset.
   void add( GeoSetPtr gset );

   //: Removes the given geoset from this geode. If the geoset does not already
   //  contain the given geoset, no work is done.
   void remove( const GeoSetPtr gset );

   //: Removes all geosets from this geode.
   void removeAll();

   //: Returns the number of geosets in this geode.
   int getNumGeoSets() const;

   //: Returns the geoset at the given index in this geode.
   GeoSetPtr getGeoSet( int idx );
   const GeoSetPtr getGeoSet( int idx ) const;

   //: Returns the list of all geosets in this geode.
   const std::vector<GeoSetPtr> getGeoSets() const;

   //: Gets the name of this geode.
   std::string getName() const;

   //: Sets the name of this geode.
   void setName( const std::string &name );

private:
   std::string mName;
   std::vector<GeoSetPtr> mGeoSets;
};

#endif // ! GEODE_H_INCLUDED

#ifndef GEODE_H_INCLUDED
#define GEODE_H_INCLUDED

#include "GeoSet.h"

//: Defines a collection of GeoSets.
class Geode : public RefObj
{
public:
   //: Adds the given geoset to this geode. The geoset is added to the end of
   //  the list of geosets. The geoset will be deleted when this geode is
   //  destroyed unless you maintained a safe_ptr to that geoset.
   void add( GeoSet *gset );

   //: Removes the given geoset from this geode. If the geoset does not already
   //  contain the given geoset, no work is done.
   void remove( const GeoSet *gset );

   //: Returns the number of geosets in this geode.
   int getNumGeoSets() const;

   //: Returns the geoset at the given index in this geode.
   GeoSet* getGeoSet( int idx );
   const GeoSet* getGeoSet( int idx ) const;

   //: Returns the list of all geosets in this geode.
   const std::vector< safe_ptr<GeoSet> > getGeoSets() const;

private:
   std::vector< safe_ptr<GeoSet> > mGeoSets;
};

#endif // ! GEODE_H_INCLUDED

#include <assert.h>
#include "Geode.h"

//------------------------------------------------------------------------------

Geode::Geode()
   : mName( "" )
{
}

//------------------------------------------------------------------------------

void
Geode::add( GeoSet *gset )
{
   mGeoSets.push_back( gset );
}

//------------------------------------------------------------------------------

void
Geode::remove( const GeoSet *gset )
{
   std::vector< safe_ptr<GeoSet> >::iterator itr;
   for ( itr = mGeoSets.begin(); itr != mGeoSets.end(); itr++ ) {
      if ( (*itr) == gset ) {
         mGeoSets.erase( itr );
      }
   }
}

//------------------------------------------------------------------------------

void
Geode::removeAll()
{
   mGeoSets.erase( mGeoSets.begin(), mGeoSets.end() );
}

//------------------------------------------------------------------------------

int
Geode::getNumGeoSets() const
{
   return mGeoSets.size();
}

//------------------------------------------------------------------------------

GeoSet*
Geode::getGeoSet( int idx )
{
   assert( (idx >= 0) && (idx < mGeoSets.size()) && "Accessing an element "
         "outside the bounds of the geoset vector");
   return mGeoSets[idx];
}

//------------------------------------------------------------------------------

const GeoSet*
Geode::getGeoSet( int idx ) const
{
   assert( (idx >= 0) && (idx < mGeoSets.size()) && "Accessing an element "
         "outside the bounds of the geoset vector");
   return mGeoSets[idx];
}

//------------------------------------------------------------------------------

const std::vector< safe_ptr<GeoSet> >
Geode::getGeoSets() const
{
   return mGeoSets;
}

//------------------------------------------------------------------------------

std::string
Geode::getName() const
{
   return mName;
}

//------------------------------------------------------------------------------

void
Geode::setName( const std::string &name )
{
   mName = name;
}

//------------------------------------------------------------------------------

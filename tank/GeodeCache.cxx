
#include "GeodeCache.h"

//------------------------------------------------------------------------------

GeodeCache::GeodeCache()
   : mImporter()
{
}

//------------------------------------------------------------------------------

GeodeCache::~GeodeCache()
{
}

//------------------------------------------------------------------------------

bool
GeodeCache::load( safe_ptr<Geode> &geode, const std::string &name )
{
   // first check if the geode is already in the cache
   std::map< std::string, safe_ptr<Geode> >::const_iterator itr;
   itr = mCache.find( name );
   if ( itr != mCache.end() ) {
//      std::cout<<"\t"<<name<<" was found in the cache\n"<<std::flush;
      // this geode is already in the cache, return a pointer to it
      geode = itr->second;
      return true;
   }

   // the geode is not in the cache, try to pull it in from the disk
   safe_ptr<Geode> geom = new Geode();
   mImporter.load( geom, name );
   assert( geom->getNumGeoSets() > 0 && "GeodeCache - ObjImporter load failed" );

   // loading was unsuccessful, return an error
   if ( geom->getNumGeoSets() <= 0 ) {
      geode = NULL;
      return false;
   }
   
   //the loading was successful, cache the geode and return a pointer to it
   mCache[name] = geom;
   geode = geom;
   return true;
}

//------------------------------------------------------------------------------

void
GeodeCache::clear()
{
   // let the safe_ptrs do the actual derefing and deletion for us
   mCache.erase( mCache.begin(), mCache.end() );
}

//------------------------------------------------------------------------------

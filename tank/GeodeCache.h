#ifndef GEODECACHE_H_INCLUDED
#define GEODECACHE_H_INCLUDED

#include <map>
#include <string>
#include "Geode.h"
#include "ObjImporter.h"

//: This singleton caches geodes so that they do not have to be re-retrieved
//  from the disk each time an entity needs the load its model.
class GeodeCache : public kev::Singleton< GeodeCache >
{
public:
   //: This is a singleton class. Use GeodeCache::instance() instead.
   GeodeCache();
   virtual ~GeodeCache();

   //: Loads the geode with the given name. If the geode is in the cache, a
   //  pointer to that geode is returned. Otherwise, the geode will be loaded
   //  from disk and put in the cache. Then the geode variable will be replaced
   //  with a pointer to the new geode.
   //
   //  Returns true if the operation was successful and geode was modified,
   //  false otherwise.
   bool load( GeodePtr& geode, const std::string &name );

   //: Clears the cache. All references to geodes currently in the cache will be
   //  released and possibly deleted if there are no remaining references to
   //  them.
   void clear();

private:
   std::map< std::string, GeodePtr > mCache;
   kev::ObjImporter mImporter;
};

#endif // ! GEOSETCACHE_H_INCLUDED

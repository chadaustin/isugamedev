
#include "World.h"

/*----------------------------------------------------------------------------*/

World::World()
{
}

/*----------------------------------------------------------------------------*/

World::~World()
{
}

/*----------------------------------------------------------------------------*/

void
World::draw() const
{
   // Draw every entity in the world. In other words, do really bad object
   // culling (none) and then draw.
   std::vector< safe_ptr<Entity> >::const_iterator itr;
   for (itr = mEntities.begin(); itr != mEntities.end(); itr++) {
      (*itr)->draw();
   }
}

/*----------------------------------------------------------------------------*/

void
World::update( float timeDelta )
{
   // Update every entity in the world. This will be extremely slow when there
   // is a large number of entities in the world.
   std::vector< safe_ptr<Entity> >::iterator itr;
   for (itr = mEntities.begin(); itr != mEntities.end(); itr++) {
      (*itr)->update( timeDelta );
   }
}

/*----------------------------------------------------------------------------*/

void
World::add( Entity *entity )
{
   mEntities.push_back( entity );
}

/*----------------------------------------------------------------------------*/

void
World::remove( Entity *entity )
{
   std::vector< safe_ptr<Entity> >::iterator itr;
   for (itr = mEntities.begin(); itr != mEntities.end(); itr++) {
      if ( (*itr) == entity ) {
         mEntities.erase(itr);
         break;
      }
   }
}

/*----------------------------------------------------------------------------*/

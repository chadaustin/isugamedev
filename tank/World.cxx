
#include <GL/glut.h>
#include "World.h"
#include "glRenderLight.h"

//------------------------------------------------------------------------------

World::World()
{
}

//------------------------------------------------------------------------------

World::~World()
{
}

//------------------------------------------------------------------------------

void
World::draw() const
{
   // Setup the lights in the world
   glEnable( GL_LIGHTING );
   std::map< int, Light >::const_iterator itr;
   for ( itr = mLights.begin(); itr != mLights.end(); itr++ ) {
      kev::glRender( itr->second );
   }

   // Draw every entity in the world. In other words, do really bad object
   // culling (none) and then draw.
   std::vector<EntityPtr>::const_iterator eitr;
   for (eitr = mEntities.begin(); eitr != mEntities.end(); eitr++) {
      (*eitr)->draw();
   }
}

//------------------------------------------------------------------------------

void
World::update( float timeDelta )
{
   // Update every entity in the world. This will be extremely slow when there
   // is a large number of entities in the world.
   std::vector<EntityPtr>::iterator itr;
   for (itr = mEntities.begin(); itr != mEntities.end(); itr++) {
      (*itr)->update( timeDelta );
   }
}

//------------------------------------------------------------------------------

void
World::add( EntityPtr entity )
{
   mEntities.push_back( entity );
}

//------------------------------------------------------------------------------

void
World::remove( EntityPtr entity )
{
   std::vector<EntityPtr>::iterator itr;
   for (itr = mEntities.begin(); itr != mEntities.end(); itr++) {
      if ( (*itr) == entity ) {
         mEntities.erase(itr);
         break;
      }
   }
}

//------------------------------------------------------------------------------

void
World::setLight( const Light &light )
{
   mLights[light.number()] = light;
}

//------------------------------------------------------------------------------

Light&
World::getLight( int lightID )
{
   return mLights[ lightID ];
}

//------------------------------------------------------------------------------

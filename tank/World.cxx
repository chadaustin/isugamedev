
#include <GL/glut.h>
#include <vector>
#include "World.h"
#include "glRenderLight.h"

typedef std::vector<EntityPtr> EntityList;

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
   const EntityList &entities = mSystem.entities();
   EntityList::const_iterator eitr;
   for (eitr = entities.begin(); eitr != entities.end(); eitr++) {
      (*eitr)->draw();
   }
}

//------------------------------------------------------------------------------

void
World::update( float timeDelta )
{
   // Update every entity in the world. This will be extremely slow when there
   // is a large number of entities in the world.
   EntityList &entities = mSystem.entities();
   EntityList::iterator itr;
   for (itr = entities.begin(); itr != entities.end(); itr++) {
      (*itr)->update( timeDelta );
   }
}

//------------------------------------------------------------------------------

void
World::add( EntityPtr entity )
{
   mSystem.add( entity );
}

//------------------------------------------------------------------------------

void
World::remove( EntityPtr entity )
{
   EntityList &entities = mSystem.entities();
   EntityList::iterator itr;
   for (itr = entities.begin(); itr != entities.end(); itr++) {
      if ( (*itr) == entity ) {
         entities.erase(itr);
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

#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <vector>
#include <map>
#include "Entity.h"
#include "Light.h"

typedef boost::shared_ptr<Entity> EntityPtr;

//: Container class for entities. Eventually the world will control all aspects
//  of the rendered environment including lights, particle engines, etc.
//
//  TODO: Entities should be stored in a database and accessed through a spatial
//  index so we can get at them in O(lg n) time rather than O(n) time.
class World
{
public:
   //: Creates a new world with no entities.
   World();

   //: Destroys this world and releases all entites in it.
   ~World();

   //: Draws this world.
   void draw() const;

   //: Updates the state of this world based on the amount of time that has
   //  passed. The world will tell each entity to update itself.
   void update( float timeDelta = 1.0f );

   //: Adds the given entity to this world.
   void add( EntityPtr entity );

   //: Removes the given entity from this world. If the entity is not in this
   //  world, this method will fail silently.
   void remove( EntityPtr entity );

   //: Sets the lighting properties for the light with ID matching the given
   //  light. This can also be used to disable lights.
   void setLight( const Light &light );

   //: Gets the light with the given light ID.
   Light& getLight( int lightID );

private:
   std::vector<EntityPtr> mEntities;
   std::map< int, Light > mLights;
};

#endif // ! WORLD_H_INCLUDED

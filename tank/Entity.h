#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <vector>
#include <boost/smart_ptr.hpp>
#include "Vec3.h"
#include "Quat.h"
#include "Matrix4f.h"
#include "Geode.h"
#include "UIDManager.h"
#include "Fizix/Body.h"

//: Describes a generic spatial object with a visual appearance charactarized by
//  geometry sets and a behavior.
class Entity : public ani::Body
{
public:
   typedef UIDManager<Entity>::UID UID;

public:
   Entity();

   //: Draws this entity as described by its geometry sets.
   void draw() const;

   //: Updates this entity based on the amount of time that has passed.
   void update( float timeDelta = 1.0f );

   //: Translates this entity using the given offset
   void translate( const Vec3f& offset );

   //: Rotates this entity deg degrees around the given normalized axis.
   void rotate( float deg, float x, float y, float z);

   //: Sets the geometry describing the visual appearance of this entity. This
   //  entity will destroy the geode upon when it is released unless you
   //  maintain a safe_ptr to it.
   void setGeode( GeodePtr geode );

   //: Gets the geode associated with this entity.
   GeodePtr getGeode();
   const GeodePtr getGeode() const;

   //: Gets a normalized vector pointing in the direction the entity is facing.
   Vec3f getForward() const;

   //: Gets the matrix given to OpenGL when this entity is drawn.
   const Matrix4f& matrix() const;

   //: Get the unique ID associated with this player
   const UID& getUID() const;

private:
   UID mUID;
   Matrix4f mXForm;
   GeodePtr mGeometry;
};

typedef boost::shared_ptr<Entity> EntityPtr;

#endif //ENTITY_H_INCLUDED

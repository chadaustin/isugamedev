#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <vector>
#include "RefObj.h"
#include "Vec3.h"
#include "Quat.h"
#include "Matrix4f.h"
#include "Geode.h"
#include "Behavior.h"
#include "UIDManager.h"

//: Describes a generic spatial object with a visual appearance charactarized by
//  geometry sets and a behavior.
class Entity : public RefObj
{
public:
   typedef UIDManager<Entity>::UID UID;

public:
   Entity();

   //: Draws this entity as described by its geometry sets.
   void draw() const;

   //: Updates this entity based on the amount of time that has passed.
   void update( float timeDelta = 1.0f );

   //: Sets the position of this entity.
   void setPos( const Vec3f& pos );

   //: Sets the rotation for the entity.
   void setRot( const Quat<float>& rot );

   //: Translates this entity using the given offset
   void translate( const Vec3f& offset );

   //: Rotates this entity deg degrees around the given normalized axis.
   void rotate( float deg, float x, float y, float z);

   //: Sets the geometry describing the visual appearance of this entity. This
   //  entity will destroy the geode upon when it is released unless you
   //  maintain a safe_ptr to it.
   void setGeode( Geode *geode );

   //: Gets the geode associated with this entity.
   Geode* getGeode();
   const Geode* getGeode() const;

   //: Sets the behavior model for this entity.
   void setBehavior( Behavior *behavior );

   //: Gets the behavior model for this entity.
   const Behavior* behavior() const;

   //: Gets a normalized vector pointing in the direction the entity is facing.
   Vec3f getForward() const;

   //: Gets the matrix given to OpenGL when this entity is drawn.
   const Matrix4f& matrix() const;

   //: Gets the position of this entity is world coordinates.
   const Vec3f& position() const;

   //: Gets the rotation of this entity.
   const Quat<float>& rotation() const;
   
   //: Get the unique ID associated with this player
   const UID& getUID() const;

private:
   UID mUID;
   Vec3f mPos;
   Quat<float> mRot;
   Matrix4f mXForm;
   safe_ptr<Behavior> mBehavior;
   safe_ptr< Geode> mGeometry;
};

#endif //ENTITY_H_INCLUDED

#ifndef OBJECT_H
#define OBJECT_H

#include "net/OutputStream.h"
#include "net/InputStream.h"
#include "net/Serialize.h"
#include "ObjectTypes.h"
#include "UIDManager.h"
#include <gmtl/Vec.h>

namespace game {
   class Object {
   public:
      /// UIDManager for objects
      typedef UIDManager<Object,PRUint32,1> UIDMgr;

      /// The UID type for objects.
      typedef UIDMgr::UID UID;

      /// The UID reserved for UNKNOWN players.
      static const UID UNKNOWN;

   public:
      Object();
      virtual ~Object();

      /**
       * Gets the unique ID associated with this object.
       */
      const UID& getUID() const;

      /**
       * Gets the position vector associated with this object.
       */
      const gmtl::Vec3f& getPosition() const {
         return mPosition;
      }

      /**
       * Sets the position vector associated with this object.
       */
      void setPosition(const gmtl::Vec3f& pos) {
         mPosition = pos;
      }

      /**
       * Gets the velocity vector associated with this object.
       */
      const gmtl::Vec3f& getVelocity() const {
         return mVelocity;
      }

      /**
       * Sets the Velocity vector associated with this object.
       */
      void setVelocity(const gmtl::Vec3f& velocity) {
         mVelocity = velocity;
      }

      /**
       * Gets the health associated with this object.
       */
      const PRFloat64& getHealth() const;

      /**
       * Sets the position vector associated with this object.
       */
      void setHealth(PRFloat64& health);

      virtual PRUint32 getType();
      virtual PRUint32 getSize();
      virtual void serialize(net::OutputStream& os);
      virtual void deserialize(net::InputStream& os);

   private:
      /// This object's UID
      UID mUID;

      /// This object's position vector
      gmtl::Vec3f mPosition;

      /// This object's velocity vector
      gmtl::Vec3f mVelocity;

      /// This object's health
      PRFloat64 mHealth;
   };
}

#endif

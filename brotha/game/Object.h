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
      const gmtl::Vec<PRFloat64,3>& getPosition() const {
         return m_position;
      }

      /**
       * Sets the position vector associated with this object.
       */
      void setPosition(const gmtl::Vec<PRFloat64,3>& pos) {
         m_position = pos;
      }

      /**
       * Gets the velocity vector associated with this object.
       */
      const gmtl::Vec<PRFloat64,3>& getVelocity() const {
         return m_velocity;
      }

      /**
       * Sets the position vector associated with this object.
       */
      void setVelocity(const gmtl::Vec<PRFloat64,3>& velocity) {
         m_velocity = velocity;
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
      gmtl::Vec<PRFloat64,3> m_position;

      /// This object's velocity vector
      gmtl::Vec<PRFloat64,3> m_velocity;

      /// This object's health
      PRFloat64 m_health;
   };
}

#endif

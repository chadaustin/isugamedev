#ifndef OBJECT_H
#define OBJECT_H

#include "net/OutputStream.h"
#include "net/InputStream.h"
#include "net/Serialize.h"
#include "ObjectTypes.h"
#include "UIDManager.h"

namespace game {
   class Object {
   public:
      /**
      * The UID type for objects.
      */
      typedef UIDManager<Object>::UID UID;
   public:
      Object();
      ~Object();

      /**
       * Gets the unique ID associated with this object.
       */
      const UID& getUID() const;

      /**
       * Gets the position vector associated with this object.
       */
      const std::vector<PRFloat64>& getPosition() const;

      /**
       * Sets the position vector associated with this object.
       */
      void setPosition(std::vector<PRFloat64>& velocity);

      /**
       * Gets the velocity vector associated with this object.
       */
      const std::vector<PRFloat64>& getVelocity() const;

      /**
       * Sets the position vector associated with this object.
       */
      void setVelocity(std::vector<PRFloat64>& velocity);

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

   protected:
      PRUint32 getVarSize(const bool var) {
         return PRUint32(sizeof(PRUint32));
      }

      PRUint32 getVarSize(const PRUint32 &var) {
         return PRUint32(sizeof(PRUint32));
      }

      PRUint32 getVarSize(const PRFloat64 &var) {
         return PRUint32(sizeof(PRFloat64));
      }

      PRUint32 getVarSize(const std::string &var) {
         return PRUint32(sizeof(PRUint32) + var.length());
      }

   private:
      /// This object's UID
      UID mUID;

      /// This object's position vector
      std::vector<PRFloat64> m_position;

      /// This object's velocity vector
      std::vector<PRFloat64> m_velocity;
 
      /// This object's health
      PRFloat64 m_health;
   };
}

#endif

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

      virtual PRUint32 getType() const = 0;
      virtual PRUint32 getSize() = 0;
      virtual void serialize(net::OutputStream& os) = 0;
      virtual void deserialize(net::InputStream& os) = 0;

   protected:
      PRUint32 getVarSize(const PRUint32 &var) {
         return PRUint32(sizeof(PRUint32));
      }

      PRUint32 getVarSize(const std::string &var) {
         return PRUint32(sizeof(PRUint32) + var.length());
      }

   private:
      /// This object's UID
      UID mUID;
   };
}

#endif

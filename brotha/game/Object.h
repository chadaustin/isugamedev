#ifndef OBJECT_H
#define OBJECT_H

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
   private:
      /// This object's UID
      UID mUID;
   };
}

#endif

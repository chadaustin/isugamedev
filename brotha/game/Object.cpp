#include "Object.h"

namespace game {
   Object::Object() {
      mUID = UIDManager<Object>::getInstance().reserveID();
   }

   Object::~Object() {
      UIDManager<Object>::getInstance().releaseID( mUID );
   }

   const Object::UID& Object::getUID() const
   {
      return mUID;
   }
}

#include "Object.h"

namespace game {
   const Object::UID Object::UNKNOWN = 0;

   Object::Object()
      : mHealth(0) {
      mUID = UIDMgr::getInstance().reserveID();
   }

   Object::~Object() {
      UIDMgr::getInstance().releaseID( mUID );
   }

   const Object::UID& Object::getUID() const {
      return mUID;
   }

   PRUint32 Object::getType() {
      return NoObject;
   }

   PRUint32 Object::getSize() {
      return net::sizes::getVarSize((PRUint32)mUID)
           + net::sizes::getVarSize(mHealth);
   }

   void Object::serialize(net::OutputStream& os) {
      os << mUID;
      os << mHealth;
   }

   void Object::deserialize(net::InputStream& is) {
      is >> mUID;
      is >> mHealth;
   }
}

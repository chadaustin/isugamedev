#include "Object.h"

namespace game {
   Object::Object() {
      mUID = UIDManager<Object>::getInstance().reserveID();
      m_velocity.resize(3);
      m_position.resize(3);
   }

   Object::~Object() {
      UIDManager<Object>::getInstance().releaseID( mUID );
   }

   const Object::UID& Object::getUID() const {
      return mUID;
   }

   PRUint32 Object::getType() {
      return NoObject;
   }

   PRUint32 Object::getSize() {
      return getVarSize((PRUint32)mUID) + getVarSize(m_position[0])*3 +
             getVarSize(m_velocity[0])*3 + getVarSize(m_health);
   }

   void Object::serialize(net::OutputStream& os) {
   }

   void Object::deserialize(net::InputStream& os) {
   }
}

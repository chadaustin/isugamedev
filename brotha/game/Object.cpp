#include "Object.h"

namespace game {
   Object::Object() {
      mUID = UIDManager<Object, PRUint32>::getInstance().reserveID();
   }

   Object::~Object() {
      UIDManager<Object, PRUint32>::getInstance().releaseID( mUID );
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
      os << mUID;
      os << m_position[0] << m_position[1] << m_position[2];
      os << m_velocity[0] << m_velocity[1] << m_velocity[2];
      os << m_health;
   }

   void Object::deserialize(net::InputStream& is) {
      is >> mUID;
      is >> m_position[0] >> m_position[1] >> m_position[2];
      is >> m_velocity[0] >> m_velocity[1] >> m_velocity[2];
      is >> m_health;
   }
}

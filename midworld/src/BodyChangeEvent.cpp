#include "BodyChangeEvent.h"
#include "RigidBody.h"

namespace mw
{
   BodyChangeEvent::BodyChangeEvent(RigidBody* src)
      : mSource(src)
   {}

   RigidBody*
   BodyChangeEvent::getSource() const
   {
      return mSource;
   }
}

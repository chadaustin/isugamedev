
#include "AbstractEntity.h"

namespace mw
{
   AbstractEntity::AbstractEntity()
      : mModel(0)
   {
      mUID = UIDManager<AbstractEntity, Entity::UID>::getInstance().reserveID();
   }

   AbstractEntity::~AbstractEntity()
   {
      UIDManager<AbstractEntity, Entity::UID>::getInstance().releaseID(mUID);
   }

   int
   AbstractEntity::getModel() const
   {
      return mModel;
   }

   void
   AbstractEntity::setModel(int model)
   {
      mModel = model;
   }

   const
   Entity::UID& AbstractEntity::getUID() const
   {
      return mUID;
   }
}

#ifndef MW_BODY_CHANGE_LISTENER_H
#define MW_BODY_CHANGE_LISTENER_H

#include "BodyChangeEvent.h"

namespace mw
{
   class BodyChangeListener
   {
   public:
      virtual ~BodyChangeListener() {}

      virtual void bodyChanged(const BodyChangeEvent& evt) = 0;
   };
}

#endif

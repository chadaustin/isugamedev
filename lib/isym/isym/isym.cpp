
#include "isym.h"

namespace isym
{
   Symbol getUID()
   {
      static Symbol ____counter = 0;
      return ++____counter;
   }   
} // end of namespace

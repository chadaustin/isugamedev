#ifndef SIREN_UTILITY_H
#define SIREN_UTILITY_H

#include <assert.h>

namespace siren
{
   // this should go into Debug.h someday
   #ifdef _MSC_VER
      #ifdef _DEBUG
         #define DBG_BREAK() do { __asm int 3 } while (false)
      #else
         #define DBG_BREAK() do { ; } while (false)
      #endif
   #else
      #define DBG_BREAK() assert(false && "Breakpoint reached")
   #endif

   /**
    * A lightweight identifier you can pass to overloaded functions to typeify
    * them.
    *
    * Type2Type lets you transport the type information about T to functions.
    */
   template< typename T >
   struct Type2Type
   {
      typedef T OriginalType;
   };
}

#endif

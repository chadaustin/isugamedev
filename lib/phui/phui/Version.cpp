#include "Version.h"

// These helper macros are used to stringify a given macro
#define PHUI_STR(s)             # s
#define PHUI_XSTR(s)            PHUI_STR(s)

// These helper macros are used to build up the PHUI_VERSION_STRING macro.
#define PHUI_DOT(a,b)           a ## . ## b
#define PHUI_XDOT(a,b)          PHUI_DOT(a,b)

//--------------------------------------------------------------------------
// Define the PHUI_VERSION_STRING macros
//--------------------------------------------------------------------------

// Create the PHUI_VERSION_STRING macro
#define PHUI_VERSION_STRING \
   PHUI_XDOT( \
      PHUI_XDOT(PHUI_VERSION_MAJOR, PHUI_VERSION_MINOR), \
      PHUI_VERSION_PATCH \
   )

namespace phui
{
   const char* version = PHUI_XSTR(PHUI_VERSION_STRING);
}

// Undef all the helper macros
#undef PHUI_XSTR
#undef PHUI_STR
#undef PHUI_DOT
#undef PHUI_XDOT

// Undef the PHUI_VERSION_STRING temporary macro
#undef PHUI_VERSION_STRING


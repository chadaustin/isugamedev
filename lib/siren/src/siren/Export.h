#ifndef SIREN_EXPORT_H
#define SIREN_EXPORT_H


#ifdef WIN32
  
   #ifdef SIREN_EXPORTS
      #define SIREN_EXPORT(ret) __declspec(dllexport) ret __stdcall
      #define SIREN_CLASS       __declspec(dllexport)
   #else
      #define SIREN_EXPORT(ret) __declspec(dllimport) ret __stdcall
      #define SIREN_CLASS       __declspec(dllimport)
   #endif
   
   #ifdef _MSC_VER
      #pragma warning(disable : 4251)
   #endif
   
#else

   #define SIREN_EXPORT(ret) ret
   #define SIREN_CLASS

#endif


#endif

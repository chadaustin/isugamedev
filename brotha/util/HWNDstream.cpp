#include "HWNDstream.h"

namespace util {
#undef WIN32
#ifdef WIN32
   HWNDostream *log = NULL;

   HWNDstreambuf::HWNDstreambuf(HWND wnd, int size /*= 0*/)
      : std::streambuf(), m_wnd(wnd) {
      if(size) {
         char *ptr = new char[size];
         setp(ptr, ptr + size);
      } else {
         setp(0,0);
      }
      setg(0,0,0);
   }

   HWNDstreambuf::~HWNDstreambuf() {
      sync();
      delete[] pbase();
   }

   void HWNDstreambuf::putBuffer() {
      if(pbase() != pptr()) {
         __w64 int len = (pptr() - pbase());
         char *str = new char[len + 1];

         strncpy(str, pbase(), len);
         str[len] = 0;
         addToWindow(str);
         setp(pbase(), epptr());
         delete [] str;
      }
   }

   void HWNDstreambuf::putChar(char ch) {
      char str[2];
      str[0] = ch;
      str[1] = 0;
      addToWindow(str);
   }

   void HWNDstreambuf::addToWindow(char *str) {
      char oldText[4096];
      int oldSize = GetWindowText(m_wnd, oldText, 4096);
      char *newText = new char[oldSize + strlen(str) + 1];
      strcpy(newText, oldText);
      strcat(newText, str);
      SetWindowText(m_wnd, newText);
      delete newText;
   }

   int HWNDstreambuf::overflow(int ch) {
      putBuffer();
      if(ch != EOF) {
         if(pbase() == epptr()) {
            putChar(ch);
         } else {
            sputc(ch);
         }
      }
      return 0;
   }

   int HWNDstreambuf::sync() {
      putBuffer();
      return 0;
   }

   HWNDostream::HWNDostream(HWND wnd, int size /*=0*/)
      : std::ostream(new HWNDstreambuf(wnd, size)) {
   }
#endif
}
#ifndef HWND_STREAM_H
#define HWND_STREAM_H

#ifdef WIN32
#  include <iostream>
#  include <windows.h>
#  define LOG (*util::log)
#  define ENDL "\r\n"
#else
#  define LOG std::cout
#  define ENDL std::endl
#endif

namespace util {
#ifdef WIN32
   class HWNDstreambuf : public std::streambuf {
   public:
      HWNDstreambuf();
      HWNDstreambuf(HWND wnd, int size = 0);
      ~HWNDstreambuf();
   private:
      void putBuffer();
      void putChar(char ch);

      void addToWindow(char *str);

      HWND m_wnd;
   protected:
      virtual int_type overflow(int_type);
      virtual int sync();
   };

   class HWNDostream : public std::ostream {
   public:
      HWNDostream(HWND wnd, int size = 0);
   };

   extern HWNDostream *log;
#endif
}

#endif // HWND_STREAM_H

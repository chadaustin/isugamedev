#ifndef HWND_STREAM_H
#define HWND_STREAM_H

#include <iostream>
#include <windows.h>

class HWNDstreambuf : public std::streambuf {
public:
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

#endif // HWND_STREAM_H
#include <iostream>
#include <stdexcept>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "Application.h"

std::string GetSDLError()
{
   return SDL_GetError();
}

void ThrowSDLError(const std::string& prefix)
{
   throw std::runtime_error((prefix + ": " + GetSDLError()).c_str());
}

void run()
{
   srand(time(0));

   std::cout << "Running Load Runner" << std::endl;

   int init_flag = SDL_INIT_NOPARACHUTE | SDL_INIT_VIDEO | SDL_INIT_TIMER;
   if(SDL_Init(init_flag) < 0)
   {
      ThrowSDLError("SDL Initialization failed");
   }

   const SDL_VideoInfo* info = SDL_GetVideoInfo();
   if (!info)
   {
      ThrowSDLError("REtrieving video information failed");
   }

   // minimum for a GL window
   SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
   SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
   SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
   SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

   const int win_width = 1024;
   const int win_height = 768;

   if(!SDL_SetVideoMode(win_width, win_height, info->vfmt->BitsPerPixel, SDL_OPENGL))
   {
      ThrowSDLError("Setting video mode failed");
   }

   // set the window caption
   std::string title = std::string("Load Runner");
   SDL_WM_SetCaption(title.c_str(), 0);
   
   std::auto_ptr<lr::Application> app(new lr::Application);

   app->resize(win_width, win_height);
   lr::u64 last_time = SDL_GetTicks();
   while(!app->shouldQuit())
   {
      SDL_Event event;
      int result = SDL_PollEvent(&event);
      bool should_quit = false;
      while(result == 1)
      {
         switch(event.type)
         {
            case SDL_VIDEORESIZE:
               app->resize(event.resize.w, event.resize.h);
               break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
               app->onKeyPress(event.key.keysym.sym, 
                               event.key.state==SDL_PRESSED);
               break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
               app->onMousePress(event.button.button,
                                 event.button.state == SDL_PRESSED,
                                 event.button.x, event.button.y);
               break;
            case SDL_MOUSEMOTION:
               app->onMouseMove(event.motion.x, event.motion.y);
               break;
            case SDL_QUIT:
               should_quit = true;
               break;
         }

         result = SDL_PollEvent(&event);
      }

      if(result < 0 || should_quit)
      { 
         break;
      }

      lr::u64 now = (lr::u64)SDL_GetTicks();

      now *=1000;

      if(now >= last_time)
      {
         app->update(now - last_time);
         app->draw();
         SDL_GL_SwapBuffers();
      }

      last_time = now;


   }

   SDL_Quit();
}

void error(const std::string& error);

int main()
{
   try
   {
      run();
   }
   catch (const std::exception& e)
   {
      error(std::string("Caught exception: ") + e.what());
   }

   return 0;
}

#ifdef WIN32

#include <windows.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   // set the current path to where the executable resides
   char filename[MAX_PATH];
   GetModuleFileName(GetModuleHandle(0), filename, MAX_PATH);

   // remove the basename
   char* backslash = strrchr(filename, '\\');
   if (backslash)
   {
      *backslash = 0;
      SetCurrentDirectory(filename);
   }
   // call our own main function from in here
   return main();
}

void error(const std::string& error)
{
  MessageBox(NULL, error.c_str(), "Racer Error", MB_ICONERROR);
}

#else

void error(const std::string& error)
{
  std::cerr << error << std::endl;
}

#endif

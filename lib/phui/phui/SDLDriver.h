#ifndef PHUI_SDL_DRIVER_H
#define PHUI_SDL_DRIVER_H

#include <phui/Driver.h>
#include <SDL/SDLInclude.h>
#include <string>

namespace phui
{
   class SDLDriver : public Driver
   {
   public:
      
      /**
       * Default Constructor
       * Sets up the SDL subsystems if running
       * in standalone mode.
       *
       * @param   standalone     true if we are running in standalone mode,
       *                         false otherwise.
       */
      SDLDriver(bool standalone = true);

      /**
       * Destructor
       * Cleans up everything phui related.
       */
      virtual ~SDLDriver();

      virtual std::string getDriverName()
      {
         return "SDL Driver";
      }

      virtual std::string getDriverVersion()
      {
         return "0.0.1";
      }

      virtual void registerRoot(RootWidgetPtr root);

      virtual void onKeyDown(InputKey key);

      virtual void onKeyUp(InputKey key);

      virtual void onMouseDown(InputButton button, const Point& p);

      virtual void onMouseUp(InputButton button, const Point& p);

      virtual void onMouseMove(const Point& p);

      virtual void start();

      /**
       * Updates phui by retrieving events from the event queue.
       * This driver will only pull events off of the queue that it is
       * interested in (keyboard/mouse); all other events will be left
       * on the event queue.
       */
      virtual void update();

      virtual bool isStandalone()
      {
         return mStandalone;
      }
 
   private:

      /// Are we running in standalone or module mode?
      bool                 mStandalone;
      
      /// The root widget.
      WidgetPtr            mRootWidget;

      /**
       * Converts an SDL_MOUSEMOTION event into a phui::Point.
       *
       * @param   event    the mouse motion event to convert.
       * @param   point    the point that will contain the mouse motion event.
       */
      void sdlMouseMotionToPhui(const SDL_MouseMotionEvent& event,
                                Point& point);

      /**
       * Converts an SDL_MOUSEBUTTON event into a phui::InputButton and
       * phui::Point.
       *
       * @param   event    the mouse button event to convert.
       * @param   button   the phui::Button.
       * @param   point    the phui::Point.
       */
      void sdlMouseButtonToPhui(const SDL_MouseButtonEvent& event,
                                InputButton& button,
                                Point& point);

      /**
       * Converts and SDL_KEY event into a phui::InputKey.
       *
       * @param   event    the key event to convert.
       * @param   key      the phui::InputKey to contain the result.
       */
      void sdlKeyToPhui(const SDL_KeyboardEvent& event,
                        InputKey& key);
   };
}

#endif

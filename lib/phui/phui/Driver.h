#ifndef PHUI_DRIVER_H
#define PHUI_DRIVER_H

#include <phui/Input.h>
#include <phui/Point.h>
#include <phui/RootWidget.h>
#include <phui/Widget.h>
#include <string>

namespace phui
{
   /**
    * The interface that all drivers must adhere to.  This defines
    * a bridge that connects the low level input handling/drawing 
    * library to phui.
    * @note    Drivers should be written to operate in two modes:
    *          standalone and module.  In standalone mode, the driver
    *          will take care of _EVERYTHING_ GUI related, ie, it 
    *          will setup the Root Window using the driver-dependant
    *          API, setup the event handlers, etc.  In module mode,
    *          the driver will assume that the driver-dependant setup
    *          has been handled by the user.  It will only handle the
    *          creation and destruction of phui components.  For the sake
    *          of simplicity, drivers should default to standalone mode.
    */
   class Driver
   {
   public:
      /**
       * Gets the name of this driver.
       *
       * @return     the name of the driver.
       */
      virtual std::string getDriverName() = 0;

      /**
       * Gets the version number of this driver as a string.
       *
       * @return     the version number of this driver.
       */
      virtual std::string getDriverVersion() = 0;

      /**
       * Registers the root widget of the gui.
       *
       * @param   root     the root widget of this gui.
       */
      virtual void registerRoot(RootWidgetPtr root) = 0;

      // Event Handlers
      /**
       * Signals that a key has been pressed.
       *
       * @param   key      the key that has been pressed.
       */
      virtual void onKeyDown(InputKey key) = 0;

      /**
       * Signals that a key has been released.
       *
       * @param   key      the key that has been released.
       */
      virtual void onKeyUp(InputKey key) = 0;

      /**
       * Signals that a mouse button has been pressed.
       *
       * @param   button   the button that has been pressed.
       * @param   point    the location of the mouse cursor at the time of
       *                   the button press.
       */
      virtual void onMouseDown(InputButton button, const Point& p) = 0;

      /**
       * Signals that a mouse button has been released.
       *
       * @param   button   the button that has been released.
       * @param   point    the location of the mouse cursor at the time of
       *                   the button release.
       */
      virtual void onMouseUp(InputButton button, const Point& p) = 0;

      /**
       * Signals that the mouse cursor has been moved.
       *
       * @param   point    the point that the mouse cursor has been moved
       *                   to.
       */
      virtual void onMouseMove(const Point& p) = 0;

      /**
       * Starts the driver; only meaningful in standalone mode.
       *
       * @note Once start is called, the function will not return until
       *       the application is closed through phui.
       */
      virtual void start() = 0;

      /**
       * Tells the driver to update phui; only meaningful in module mode.
       */
      virtual void update() = 0;

      /**
       * Checks to see whether the driver is running in standalone mode or
       * module mode.
       *
       * @return     true if the driver is in standalone mode, false if it is
       *             in module mode.
       */
      virtual bool isStandalone() = 0;
   };
}

#endif

#ifndef PHUI_GLUT_DRIVER_H
#define PHUI_GLUT_DRIVER_H

#include "Driver.h"
#include <GL/glut.h>

namespace phui
{
   class GLUTDriver : public Driver
   {
   public:

      /**
       * Default Constructor
       * Sets up Windows et al using the glut library if running in
       * standalone mode.
       *
       * @param   standalone     true if we are running in standalone mode,
       *                         false otherwise
       */
      GLUTDriver(bool standalone = true);

      /**
       * Destructor
       * Cleans up everything phui related.
       */
      virtual ~GLUTDriver();

      // Inherited functions.

      std::string getDriverName()
      {
         return "Glut Driver";
      }

      std::string getDriverVersion()
      {
         return "0.0.1";
      }

      void registerRoot(RootWidgetPtr root);
      
      void onKeyDown(InputKey key);

      void onKeyUp(InputKey key);

      void onMouseDown(InputButton button, const Point& p);

      void onMouseUp(InputButton button, const Point& p);

      void onMouseMove(const Point& p);

      void start();

      void update();

      bool isStandalone()
      {
         return mStandalone;
      }

      /**
       * GLUT specific handlers necessary to get around the callback model
       * of GLUT.
       */
      void onReshape(int w, int h);
      void onDisplay();

   private:

      /// Are we running in standalone or module mode?
      bool                    mStandalone;

      /// The root widget of the display, ie, the widget that holds everything.
      WidgetPtr               mRootWidget;

      /// integer representing the argc argument for glutInit
      int                     mDummyArgc;

      /// Can the application quit yet?  (Only meaningful in standalone mode)
      bool                    mCanQuit;
   };
}
#endif

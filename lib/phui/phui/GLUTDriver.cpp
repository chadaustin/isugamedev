#include "GLUTDriver.h"
#include "DriverManager.h"
#include "Point.h"
#include <loki/Functor.h>
#include <loki/Singleton.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

namespace phui
{
   /**
    * Define all GLUT Callbacks in an anonymous namespace; this is because we 
    * are wrapping the GLUT callback model with phui, so this doesn't need to
    * be visible to anyone.
    */
   namespace
   {
      // Make a creator function for the GLUTDriver so that the driver manager
      // knows of a way to create GLUTDrivers.
      Driver* create(bool standalone)
      {
         return new GLUTDriver(standalone);
      }

      // The following registers the GLUTDriver with the driver manager; we
      // do this by creating a dummy class in an anonymous namespace that 
      // registers the GLUTDriver in its constructor.  We then instantiate
      // a static object of this dummy class inside the anonymous namespace.
      struct RegisterGLUTDriver
      {
         RegisterGLUTDriver()
         {
            DriverManager::Instance().registerDriver( "GLUT", &create );
         }
      };
      
      static RegisterGLUTDriver register_glut_driver;
      
      /// Pointer to the current GLUT Driver; this lets us workaround the
      /// callback model that GLUT uses.
      static GLUTDriver* gHackPtr = 0;

      InputKey glutToPhuiKey(char key)
      {
         if (key >= 'a' && key <= 'z')
         {
            return (InputKey)(KEY_A + (key - 'a'));
         }
         else if (key >= '0' && key <= '9') 
         {
            return (InputKey)(KEY_0 + (key - '0'));
         }

         switch (key)
         {
            case 8:   return KEY_BACKSPACE;
            case 9:   return KEY_TAB;
            case 27:  return KEY_ESCAPE;
            case 32:  return KEY_SPACE;
            case 127: return KEY_DELETE;

            default:  return KEY_UNKNOWN;
         }
      }


      InputKey glutSpecialToPhuiKey(int key)
      {
#define KEY(name) \
      case GLUT_KEY_##name: return KEY_##name

         switch (key) {
            KEY(F1);
            KEY(F2);
            KEY(F3);
            KEY(F4);
            KEY(F5);
            KEY(F6);
            KEY(F7);
            KEY(F8);
            KEY(F9);
            KEY(F10);
            KEY(F11);
            KEY(F12);
            KEY(LEFT);
            KEY(UP);
            KEY(RIGHT);
            KEY(DOWN);
            KEY(PAGE_UP);
            KEY(PAGE_DOWN);
            KEY(HOME);
            KEY(END);
            KEY(INSERT);
            default: return KEY_UNKNOWN;
         }
#undef KEY
      }

      InputButton glutToPhuiButton(int button)
      {
         switch (button) 
         {
            case GLUT_LEFT_BUTTON:   return BUTTON_LEFT;
            case GLUT_MIDDLE_BUTTON: return BUTTON_MIDDLE;
            case GLUT_RIGHT_BUTTON:  return BUTTON_RIGHT;
            default:                 return BUTTON_UNKNOWN;
         }
      }

      void glutMouseCallback(int button, int state, int x, int y)
      {
         InputButton phui_button = glutToPhuiButton(button);
         if (GLUT_DOWN == state)
         {
            gHackPtr->onMouseDown( phui_button, Point(x, y) );
         }
         else
         {
            gHackPtr->onMouseUp( phui_button, Point(x, y) );
         }
      }

      void glutMotionCallback(int x, int y)
      {
         gHackPtr->onMouseMove( Point(x, y) );
      }

      void glutKeyboardCallback(unsigned char key, int x, int y)
      {
         gHackPtr->onKeyDown( glutToPhuiKey(key) );
      }

      void glutKeyboardUpCallback(unsigned char key, int x, int y)
      {
         gHackPtr->onKeyUp( glutToPhuiKey(key) );
      }

      void glutSpecialCallback(int key, int x, int y)
      {
         gHackPtr->onKeyDown( glutSpecialToPhuiKey(key) );
      }

      void glutSpecialUpCallback(int key, int x, int y)
      {
         gHackPtr->onKeyUp( glutSpecialToPhuiKey(key) );
      }

      void glutReshapeCallback(int width, int height)
      {
         gHackPtr->onReshape(width, height);
      }

      void glutDisplayCallback()
      {
         gHackPtr->onDisplay(); 
      }
   }

   GLUTDriver::GLUTDriver(bool standalone)
      : mStandalone(standalone), mDummyArgc(1), mCanQuit(false)
   {
      if (mStandalone)
      {
         char* argv[] = { "phui" };
         glutInit(&mDummyArgc, argv);
         glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
         
         // initialize the OpenGL projection matrix.
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         glMatrixMode(GL_PROJECTION);
         glLoadIdentity();
         gluOrtho2D(0.0, 300.0, 0.0, 300.0);
         // switch the matrix mode back to modelview.
         glMatrixMode(GL_MODELVIEW);
      }
   }

   GLUTDriver::~GLUTDriver()
   {
   }

   void
   GLUTDriver::registerRoot(RootWidgetPtr root)
   {
      if (mStandalone)
      {
         glutInitWindowPosition(root->getPosition().x, root->getPosition().y);
         glutInitWindowSize( root->getSize().getWidth(), 
                             root->getSize().getHeight() );
         glutCreateWindow("PHUI");
      }
      mRootWidget = root;
   }

   void
   GLUTDriver::onKeyDown(InputKey key)
   {
      mRootWidget->onKeyDown(key);
   }

   void
   GLUTDriver::onKeyUp(InputKey key)
   {
      mRootWidget->onKeyUp(key);
   }

   void
   GLUTDriver::onMouseDown(InputButton button, const Point& p)
   {
      mRootWidget->onMouseDown(button, p);
   }

   void
   GLUTDriver::onMouseUp(InputButton button, const Point& p)
   {
      mRootWidget->onMouseUp(button, p);
   }

   void
   GLUTDriver::onMouseMove(const Point& p)
   {
      mRootWidget->onMouseMove(p);
   }
   
   void
   GLUTDriver::start()
   {
      // register callbacks
      glutDisplayFunc( glutDisplayCallback ); 
      glutMouseFunc( glutMouseCallback );
      glutMotionFunc( glutMotionCallback );
      glutPassiveMotionFunc( glutMotionCallback );
      glutKeyboardFunc( glutKeyboardCallback );
      glutKeyboardUpFunc( glutKeyboardUpCallback );
      glutSpecialFunc( glutSpecialCallback );
      glutSpecialUpFunc( glutSpecialUpCallback );
      glutReshapeFunc( glutReshapeCallback );
      // sit and spin
      glutMainLoop();
      while(!mCanQuit)
      {
         // wait to stop; the phui specification states that while in standalone
         // mode, we do not return until we are ready to quit.
      }
   }

   void
   GLUTDriver::update()
   {
      // GLUT uses a callback model, so in module mode the user must give us
      // events from their user event callback.  This function does nothing.
   }

   void
   GLUTDriver::onReshape(int w, int h)
   {
      mRootWidget->setSize( Size(w, h) );
   }

   void
   GLUTDriver::onDisplay()
   {
      mRootWidget->draw();
   }
}

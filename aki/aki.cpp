#include "GameApp.h"      // the base application type
#include "GameKernel.h"
#include "GameInput.h"
#include "AnalogInterface.h"
#include "DigitalInterface.h"
#include "GlutDriver.h"
#include "Grid.h"
                  
class AkiGame : public GameApp
{
public:
   virtual void OnAppInit()
   {
      GameInput::instance().bind( "MouseX", "Mouse", "MOUSEAXIS_X" );
      GameInput::instance().bind( "MouseY", "Mouse", "MOUSEAXIS_Y" );
      GameInput::instance().bind( "Quit", "Keyboard", "KEY_Q" );
      GameInput::instance().bind( "Accelerate", "Keyboard", "KEY_SPACE" );
      GameInput::instance().bind( "Accelerate", "Mouse", "MOUSEBUTTON_LEFT" );
      
      GameKernel::instance().setName( "Aki's Quest" );
      mQuit.init( "Quit" );
      mAccelerate.init( "Accelerate" );
      mMouseX.init( "MouseX" );
      mMouseY.init( "MouseY" );
   }
   
   virtual void OnContextInit()
   {
      GameKernel::instance().setWindowSize( 640, 480 );
   }
   
   virtual void OnContextDraw( int context = 0 )
   {
      int width, height;
      GameKernel::instance().getWindowSize( width, height );      
      glViewport( 0, 0, width, height );
      
      glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
      glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
      glEnable( GL_DEPTH_TEST );
      glEnable( GL_BLEND );
      glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); 


      // set up the projection matrix
      glMatrixMode( GL_PROJECTION );
         glLoadIdentity();               
         gluPerspective( 100.0f, width / height, 0.01f, 1000.0f );

      // initialize your matrix stack used for transforming your models
      glMatrixMode( GL_MODELVIEW );
      glLoadIdentity();      

      glTranslatef( 0, -4, 0 );
      grid.draw();
   }
   
   virtual void OnPostFrame()
   {
      if (mQuit.getDigitalData() == DigitalInput::DOWN)
      {
         GameKernel::instance().shutdown();
      }     
      
      std::cout<< "Accelerate: "
               << mAccelerate.getDigitalData() << " "
               << " MouseX: " << mMouseX.getAnalogData() << ","
               << mMouseY.getAnalogData() << std::endl;
   }   
   
public:
   Grid grid;
   AnalogInterface mMouseX, mMouseY;
   DigitalInterface mAccelerate, mQuit;
};

void main( int argc, char *argv[] )
{
   GameKernelRegister<AkiGame> reg;
   SystemDriver* driver = new GlutDriver();
   GameKernel::instance().startup( driver );
}

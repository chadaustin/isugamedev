#include "GameApp.h"      // the base application type
#include "GameKernel.h"
#include "GameInput.h"
#include "DigitalInterface.h"
           
#include "Grid.h"
                  
class AkiGame : public GameApp
{
public:
   virtual void OnAppInit()
   {
      GameKernel::instance().setName( "Aki's Quest" );
      mQuit.init( "Quit" );
      mAccelerate.init( "Accelerate" );
      
      GameInput::instance().bind( "Quit", "Keyboard", "KEY_Q" );
      GameInput::instance().bind( "Quit", "Keyboard", "KEY_q" );
      GameInput::instance().bind( "Accelerate", "Keyboard", "KEY_SPACE" );
      GameInput::instance().bind( "Accelerate", "Mouse", "MOUSEBUTTON_LEFT" );
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
               << mAccelerate.getDigitalData() << std::endl;
   }   
   
public:
   Grid grid;
   DigitalInterface mAccelerate, mQuit;
};

void main( int argc, char *argv[] )
{   
   GameKernelRegister<AkiGame> reg;
   GameKernel::instance().startup();
}

#ifndef VIRTUAL_GAME_CURSOR
#define VIRTUAL_GAME_CURSOR

#include "cubeGeometry.h" // for default draw method

namespace mw
{
   /// virtual cursor, hides system sursor, shows opengl cursor
   class Cursor
   {
   public:
      Cursor()
      {
         this->init( 640, 480 );
      }
      
      virtual ~Cursor()
      {
      }
      
      float getX() const { return mMousePosX; }
      float getY() const { return mMousePosY; }
      
      virtual void init( int w, int h )
      {
         mMousePosX = w / 2;
         mMousePosY = h / 2;
         mNeedWarp = true;
         
         // init the system mouse state...
         ::SDL_WarpMouse( w / 2, h / 2 );
         ::SDL_ShowCursor( SDL_DISABLE );
      }      
      
      /// overload this to draw your custom image.
      virtual void draw( int w, int h )
      {
         // draw cursor (dumb)
         glPushMatrix();
         glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            glOrtho(0, w, h, 0, 300, -300);
         glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            glTranslatef( mMousePosX, mMousePosY, 0 );
            glScalef( 3.0f, 3.0f, 3.0f );
            cubeGeometry().render();
            glPopMatrix();

            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
         glPopMatrix();
      }    
      
      virtual void update( int w, int h )
      {
         // keep track of the mouse cursor...
         if (mNeedWarp)
         {
            ::SDL_WarpMouse( w / 2, h / 2 );
            mNeedWarp = false;
         }
      }  
      
      virtual void onMouseMove( int w, int h, int x, int y )
      {
         // keep track of the game-draw virtual cursor
         mNeedWarp = true;
         x -= w / 2;
         y -= h / 2;
         mMousePosX += x;
         mMousePosY += y;

         // constrain virtual cursor
         if (mMousePosX < 0) mMousePosX = 0;
         if (w < mMousePosX) mMousePosX = w;
         if (mMousePosY < 0) mMousePosY = 0;
         if (h < mMousePosY) mMousePosY = h;
      }    
      
   private:
      // cursor
      float mMousePosX, mMousePosY;
      bool mNeedWarp;
   }; 
}

#endif

#include "OptionsState.h"
#include "Application.h"
#include "StateFactory.h"
#include "InputSymbol.h"
#include <fstream>

namespace mw
{
   OptionsState::OptionsState(Application* a ) : State( a )
   {
      mImages.push_back( Texture::create("unsupported") );

      mFont = 0;
      mFontRenderer = 0;
      mFont = gltext::CreateFont("fonts/arial.ttf", gltext::PLAIN, 24);
      if (!mFont)
      {
         throw std::runtime_error("Could not create gltext font: fonts/arial.ttf");
      }
      
      mFontRenderer = gltext::CreateRenderer(gltext::PIXMAP);
      if (!mFontRenderer)
      {
         delete mFont;
         mFont = 0;
         throw std::runtime_error("Could not create gltext renderer");
      }

      mFontRenderer->setFont(mFont);
      
      bindKey = false;
      currentSelection = 0;

      mInputManager.loadMappings("inputmap.cfg");
      bindings[KEY_UP] = mInputManager.getKey("MOVE UP");
      mouseBindings[KEY_UP] = mInputManager.getButton("MOVE UP");
      bindings[KEY_DOWN] = mInputManager.getKey("MOVE DOWN");
      mouseBindings[KEY_DOWN] = mInputManager.getButton("MOVE DOWN");
      bindings[KEY_LEFT] = mInputManager.getKey("MOVE LEFT");
      mouseBindings[KEY_LEFT] = mInputManager.getButton("MOVE LEFT");
      bindings[KEY_RIGHT] = mInputManager.getKey("MOVE RIGHT");
      mouseBindings[KEY_RIGHT] = mInputManager.getButton("MOVE RIGHT");
      bindings[KEY_ZOOM_IN] = mInputManager.getKey("ZOOM IN");
      mouseBindings[KEY_ZOOM_IN] = mInputManager.getButton("ZOOM IN");
      bindings[KEY_ZOOM_OUT] = mInputManager.getKey("ZOOM OUT");
      mouseBindings[KEY_ZOOM_OUT] = mInputManager.getButton("ZOOM OUT");
      bindings[KEY_PITCH_UP] = mInputManager.getKey("PITCH UP");
      mouseBindings[KEY_PITCH_UP] = mInputManager.getButton("PITCH UP");
      bindings[KEY_PITCH_DOWN] = mInputManager.getKey("PITCH DOWN");
      mouseBindings[KEY_PITCH_DOWN] = mInputManager.getButton("PITCH DOWN");
      bindings[KEY_YAW_LEFT] = mInputManager.getKey("YAW LEFT");
      mouseBindings[KEY_YAW_LEFT] = mInputManager.getButton("YAW LEFT");
      bindings[KEY_YAW_RIGHT] = mInputManager.getKey("YAW RIGHT");
      mouseBindings[KEY_YAW_RIGHT] = mInputManager.getButton("YAW RIGHT");
      bindings[KEY_SHOOT] = mInputManager.getKey("SHOOT");
      mouseBindings[KEY_SHOOT] = mInputManager.getButton("SHOOT");
      bindings[KEY_CYCLE_WEAPON] = mInputManager.getKey("CYCLE WEAPON");
      mouseBindings[KEY_CYCLE_WEAPON] = mInputManager.getButton("CYCLE WEAPON");
      bindings[KEY_QUIT] = mInputManager.getKey("QUIT");
      mouseBindings[KEY_QUIT] = mInputManager.getButton("QUIT");
    
   }

   OptionsState::~OptionsState()
   {
      delete mFont;
      delete mFontRenderer;
   }

   void OptionsState::draw()
   {
      glEnable(GL_TEXTURE_2D);
      glDisable(GL_DEPTH_TEST);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glDisable(GL_CULL_FACE);

      glClear(GL_COLOR_BUFFER_BIT);

      // set up projection matrix
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0, this->application().getWidth(), this->application().getHeight(), 0, -1, 1);

      // set up view matrix
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      glColor4f(1, 1, 1, 1);
      mImages[0]->drawRectangle(0,0,this->application().getWidth(), this->application().getHeight());	// draw background

      const int xOffset = 300;
      const int yOffset = 30;
      const int xInit = 100;
      const int yInit = 100;

      glPushMatrix();
         //Initial Position for Key Labels
         glTranslatef(xInit,yInit,0);

            glTranslatef(0,yOffset,0);
            mFontRenderer->render("Move Forward");

            glPushMatrix();
               glTranslatef(xOffset, 0, 0);
               if(bindings[KEY_UP] != SDLK_UNKNOWN)
                  mFontRenderer->render(SDLKeyToString(bindings[KEY_UP]).c_str());
               else
                  mFontRenderer->render(SDLButtonToString(mouseBindings[KEY_UP]).c_str());
            glPopMatrix();

            glTranslatef(0,yOffset,0);
            mFontRenderer->render("Move Back");

            glPushMatrix();
               glTranslatef(xOffset, 0, 0);
               if(bindings[KEY_DOWN] != SDLK_UNKNOWN)
                  mFontRenderer->render(SDLKeyToString(bindings[KEY_DOWN]).c_str());
               else
                  mFontRenderer->render(SDLButtonToString(mouseBindings[KEY_DOWN]).c_str());
            glPopMatrix();

            glTranslatef(0,yOffset,0);
            mFontRenderer->render("Move Left");

            glPushMatrix();
               glTranslatef(xOffset, 0, 0);
               if(bindings[KEY_LEFT] != SDLK_UNKNOWN)
                  mFontRenderer->render(SDLKeyToString(bindings[KEY_LEFT]).c_str());
               else
                  mFontRenderer->render(SDLButtonToString(mouseBindings[KEY_LEFT]).c_str());
            glPopMatrix();

            glTranslatef(0,yOffset,0);
            mFontRenderer->render("Move Right");

            glPushMatrix();
               glTranslatef(xOffset, 0, 0);
               if(bindings[KEY_RIGHT] != SDLK_UNKNOWN)
                  mFontRenderer->render(SDLKeyToString(bindings[KEY_RIGHT]).c_str());
               else
                  mFontRenderer->render(SDLButtonToString(mouseBindings[KEY_RIGHT]).c_str());
            glPopMatrix();

            glTranslatef(0,yOffset,0);
            mFontRenderer->render("Camera Zoom In");

            glPushMatrix();
               glTranslatef(xOffset, 0, 0);
               if(bindings[KEY_ZOOM_IN] != SDLK_UNKNOWN)
                  mFontRenderer->render(SDLKeyToString(bindings[KEY_ZOOM_IN]).c_str());
               else
                  mFontRenderer->render(SDLButtonToString(mouseBindings[KEY_ZOOM_IN]).c_str());
            glPopMatrix();

            glTranslatef(0,yOffset,0);
            mFontRenderer->render("Camera Zoom Out");

            glPushMatrix();
               glTranslatef(xOffset, 0, 0);
               if(bindings[KEY_ZOOM_OUT] != SDLK_UNKNOWN)
                  mFontRenderer->render(SDLKeyToString(bindings[KEY_ZOOM_OUT]).c_str());
               else
                  mFontRenderer->render(SDLButtonToString(mouseBindings[KEY_ZOOM_OUT]).c_str());
            glPopMatrix();

            glTranslatef(0,yOffset,0);
            mFontRenderer->render("Camera Pitch Up");

            glPushMatrix();
               glTranslatef(xOffset, 0, 0);
               if(bindings[KEY_PITCH_UP] != SDLK_UNKNOWN)
                  mFontRenderer->render(SDLKeyToString(bindings[KEY_PITCH_UP]).c_str()); 
               else
                  mFontRenderer->render(SDLButtonToString(mouseBindings[KEY_PITCH_UP]).c_str());
            glPopMatrix();

            glTranslatef(0,yOffset,0);
            mFontRenderer->render("Camera Pitch Down");

            glPushMatrix();
               glTranslatef(xOffset, 0, 0);
               if(bindings[KEY_PITCH_DOWN] != SDLK_UNKNOWN)
                  mFontRenderer->render(SDLKeyToString(bindings[KEY_PITCH_DOWN]).c_str());
               else
                  mFontRenderer->render(SDLButtonToString(mouseBindings[KEY_PITCH_DOWN]).c_str());
            glPopMatrix();

            glTranslatef(0,yOffset,0);
            mFontRenderer->render("Camera Yaw Left");
            
            glPushMatrix();
               glTranslatef(xOffset, 0, 0);
               if(bindings[KEY_YAW_LEFT] != SDLK_UNKNOWN)
                  mFontRenderer->render(SDLKeyToString(bindings[KEY_YAW_LEFT]).c_str());
               else
                   mFontRenderer->render(SDLButtonToString(mouseBindings[KEY_YAW_LEFT]).c_str());
            glPopMatrix();

            glTranslatef(0,yOffset,0);
            mFontRenderer->render("Camera Yaw Right");

            glPushMatrix();
               glTranslatef(xOffset, 0, 0);
               if(bindings[KEY_YAW_RIGHT] != SDLK_UNKNOWN)
                  mFontRenderer->render(SDLKeyToString(bindings[KEY_YAW_RIGHT]).c_str());
               else
                  mFontRenderer->render(SDLButtonToString(mouseBindings[KEY_YAW_RIGHT]).c_str());
            glPopMatrix();

            glTranslatef(0,yOffset,0);
            mFontRenderer->render("Shoot");

            glPushMatrix();
               glTranslatef(xOffset, 0, 0);
               if(bindings[KEY_SHOOT] != SDLK_UNKNOWN) 
                  mFontRenderer->render(SDLKeyToString(bindings[KEY_SHOOT]).c_str());
               else
                  mFontRenderer->render(SDLButtonToString(mouseBindings[KEY_SHOOT]).c_str());
            glPopMatrix();

            glTranslatef(0,yOffset,0);
            mFontRenderer->render("Cycles Weapons");

            glPushMatrix();
               glTranslatef(xOffset, 0, 0);
               if(bindings[KEY_CYCLE_WEAPON] != SDLK_UNKNOWN)
                  mFontRenderer->render(SDLKeyToString(bindings[KEY_CYCLE_WEAPON]).c_str());
               else
                  mFontRenderer->render(SDLButtonToString(mouseBindings[KEY_CYCLE_WEAPON]).c_str());
            glPopMatrix();
      glPopMatrix();

      //Draw Selection Box
      glPushMatrix();
         glTranslatef(xInit,yInit+(yOffset*(currentSelection+1)),0);

         if(bindKey)
         {
            glColor4f(0,0,1,0.5);

            glBegin(GL_QUADS);
               glVertex2f(-2, -20);
               glVertex2f(-2, 5);
               glVertex2f(xOffset+200, 5);
               glVertex2f(xOffset+200, -20);
            glEnd();
         }
         else
         {
            glColor3f(0,0,1);

            glBegin(GL_LINE_LOOP);
               glVertex2f(-2, -20);
               glVertex2f(-2, 5);
               glVertex2f(xOffset+200, 5);
               glVertex2f(xOffset+200, -20);
            glEnd();
         }
      glPopMatrix();

   }

   void OptionsState::onMousePress(Uint8 button, bool down, int x, int y)
   {
      
   }

   void OptionsState::onKeyPress(SDLKey sym, bool down)
   {
      if (down && !bindKey)
      {
         switch(sym)
         {
         case SDLK_ESCAPE:
            writeConfigFile();
            invokeTransition("Menu");
            break;

         case SDLK_DOWN:
            if(currentSelection == 11)
               currentSelection = 0;
            else
               currentSelection++;
            break;

         case SDLK_UP:
            if(currentSelection == 0)
               currentSelection = 11;
            else
               currentSelection--;
            break;

         case SDLK_RETURN:
            bindKey = true;
            break;
         default:
            break;
         } 
      }
      else if(down && bindKey)
      {
         bindings[currentSelection] = sym;
         mouseBindings[currentSelection] = 0;
         bindKey = false;
      }
   }

   void OptionsState::writeConfigFile()
   {
      std::ofstream outfile;

      outfile.open("inputmap.cfg");

      if(outfile.fail())
         throw std::runtime_error("Could not find an inputmap.cfg file");
      

      if(bindings[KEY_UP] != SDLK_UNKNOWN)
      {
         outfile << SDLKeyToString(bindings[KEY_UP]) << "=MOVE UP" << std::endl;
      }
      else
      {
         outfile << SDLButtonToString(mouseBindings[KEY_UP]) << "=MOVE UP" << std::endl;
      }

      if(bindings[KEY_DOWN] != SDLK_UNKNOWN)
      {
         outfile << SDLKeyToString(bindings[KEY_DOWN]) << "=MOVE DOWN" << std::endl;
      }
      else
      {
         outfile << SDLButtonToString(mouseBindings[KEY_DOWN]) << "=MOVE DOWN" << std::endl;
      }

      if(bindings[KEY_LEFT] != SDLK_UNKNOWN)
      {
         outfile << SDLKeyToString(bindings[KEY_LEFT]) << "=MOVE LEFT" << std::endl;
      }
      else
      {
         outfile << SDLButtonToString(mouseBindings[KEY_LEFT]) << "=MOVE LEFT" << std::endl;
      }

      if(bindings[KEY_RIGHT] != SDLK_UNKNOWN)
      {
         outfile << SDLKeyToString(bindings[KEY_RIGHT]) << "=MOVE RIGHT" << std::endl;
      }
      else
      {
         outfile << SDLButtonToString(mouseBindings[KEY_RIGHT]) << "=MOVE RIGHT" << std::endl;
      }


      if(bindings[KEY_ZOOM_IN] != SDLK_UNKNOWN)
      {
         outfile << SDLKeyToString(bindings[KEY_ZOOM_IN]) << "=ZOOM IN" << std::endl;
      }
      else
      {
         outfile << SDLButtonToString(mouseBindings[KEY_ZOOM_IN]) << "=ZOOM IN" << std::endl;
      }

      if(bindings[KEY_ZOOM_OUT] != SDLK_UNKNOWN)
      {
         outfile << SDLKeyToString(bindings[KEY_ZOOM_OUT]) << "=ZOOM OUT" << std::endl;
      }
      else
      {
         outfile << SDLButtonToString(mouseBindings[KEY_ZOOM_OUT]) << "=ZOOM OUT" << std::endl;
      }

      if(bindings[KEY_PITCH_UP] != SDLK_UNKNOWN)
      {
         outfile << SDLKeyToString(bindings[KEY_PITCH_UP]) << "=PITCH UP" << std::endl;
      }
      else
      {
         outfile << SDLButtonToString(mouseBindings[KEY_PITCH_UP]) << "=PITCH UP" << std::endl;
      }

      if(bindings[KEY_PITCH_DOWN] != SDLK_UNKNOWN)
      {
         outfile << SDLKeyToString(bindings[KEY_PITCH_DOWN]) << "=PITCH DOWN" << std::endl;
      }
      else
      {
         outfile << SDLButtonToString(mouseBindings[KEY_PITCH_DOWN]) << "=PITCH DOWN" << std::endl;
      }

      if(bindings[KEY_YAW_LEFT] != SDLK_UNKNOWN)
      {
         outfile << SDLKeyToString(bindings[KEY_YAW_LEFT]) << "=YAW LEFT" << std::endl;
      }
      else
      {
         outfile << SDLButtonToString(mouseBindings[KEY_YAW_LEFT]) << "=YAW LEFT" << std::endl;
      }

      if(bindings[KEY_YAW_RIGHT] != SDLK_UNKNOWN)
      {
         outfile << SDLKeyToString(bindings[KEY_YAW_RIGHT]) << "=YAW RIGHT" << std::endl;
      }
      else
      {
         outfile << SDLButtonToString(mouseBindings[KEY_YAW_RIGHT]) << "=YAW RIGHT" << std::endl;
      }

      if(bindings[KEY_SHOOT] != SDLK_UNKNOWN)
      {
         outfile << SDLKeyToString(bindings[KEY_SHOOT]) << "=SHOOT" << std::endl;
      }
      else
      {
         outfile << SDLButtonToString(mouseBindings[KEY_SHOOT]) << "=SHOOT" << std::endl;
      }

      if(bindings[KEY_CYCLE_WEAPON] != SDLK_UNKNOWN)
      {
         outfile << SDLKeyToString(bindings[KEY_CYCLE_WEAPON]) << "=CYCLE WEAPON" << std::endl;
      }
      else
      {
         outfile << SDLButtonToString(mouseBindings[KEY_CYCLE_WEAPON]) << "=CYCLE WEAPON" << std::endl;
      }

      outfile << "KEY_ESCAPE=QUIT" << std::endl;

      outfile.close();
   }
}


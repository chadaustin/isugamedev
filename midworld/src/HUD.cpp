#include <iomanip>
#include <sstream>
#include <SDL_opengl.h>
#include "Application.h"
#include "GameState.h"
#include "HUD.h"
#include "Utility.h"


namespace mw
{
   class gltextrenderer : public std::stringstream
   {
   public:
      gltextrenderer(
         gltext::FontRenderer* renderer,
         float x,
         float y,
         const gmtl::Vec4f& color)
      {
         mRenderer = renderer;
         mX = x;
         mY = y;
         mColor = color;
      }
      
      ~gltextrenderer()
      {
         glPushMatrix();
         glTranslatef(mX, mY, 0);
         glColor(mColor);
         mRenderer->render(str().c_str());
         glPopMatrix();
      }
      
   private:
      gltext::FontRenderer* mRenderer;
      float mX;
      float mY;
      gmtl::Vec4f mColor;
   };
   

   HUD::HUD()
   {
      mFont = 0;
      mFontRenderer = 0;
      mFont = gltext::CreateFont("fonts/arial.ttf", gltext::PLAIN, 24);
      if (!mFont)
      {
         throw std::runtime_error("Couldn't create gltext font: fonts/arial.ttf");
      }
      
      mFontRenderer = gltext::CreateRenderer(gltext::PIXMAP);
      if (!mFontRenderer)
      {
         delete mFont;
         mFont = 0;
         throw std::runtime_error("Couldn't create gltext renderer");
      }
      mFontRenderer->setFont(mFont);
   }

   HUD::~HUD()
   {
      delete mFont;
      delete mFontRenderer;
   }

   void HUD::draw(GameState& gs)
   {
      static const gmtl::Vec4f white(1, 1, 1, 1);
      static const gmtl::Vec4f red  (1, 0, 0, 1);
      static const gmtl::Vec4f green(0, 1, 0, 1);
      static const gmtl::Vec4f blue (0, 0, 1, 1);

      Player& player = gs.getPlayer();
      Application& app = gs.application();
      
      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
      glLoadIdentity();
      gluOrtho2D(0, app.getWidth(), app.getHeight(), 0);

      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glLoadIdentity();

      if (!player.weapon().isNull())
      {
         float weaponx = 20;
         float weapony = app.getHeight() - 30;
         gltextrenderer(mFontRenderer, weaponx, weapony, red) <<
            player.weapon().getName() << "   " <<
            player.weapon().getAmmoInClip() << " | " <<
            player.weapon().getAmmoInBag();
      }
      
      // player health
      gltextrenderer(mFontRenderer, 20, app.getHeight() - 60, green)
         << "Health: " << player.getHealth();


      // FPS
      float fpsx = app.getWidth() - 150;
      float fpsy = 20 + mFont->getAscent();
      gltextrenderer(mFontRenderer, fpsx, fpsy, white)
         << "FPS: " << std::setprecision(4) << gs.getFPS();

      glMatrixMode(GL_PROJECTION);
      glPopMatrix();
      
      glMatrixMode(GL_MODELVIEW);
      glPopMatrix();
   }

}

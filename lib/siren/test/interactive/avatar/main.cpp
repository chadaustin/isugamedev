#include <memory>
#include <stdexcept>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>
#include <gmtl/EulerAngle.h>
#include <gmtl/Math.h>
#include <siren/siren.h>
#include <siren/avatar/Avatar.h>

class AvatarState : public siren::State
{
public:
   AvatarState()
      : mRotX(0.0f)
      , mRotY(0.0f)
      , mIgnoreMouseMove(true)
   {
      mAvatar = siren::Avatar::create("John");
//      mAvatar->setDrawMode(siren::Avatar::DrawSkeleton);
//      mAvatar->triggerAnimationCycle("RUN");
//      mAvatar->triggerAnimationCycle("DANCE");
      mAvatar->setWCS(gmtl::EulerAngleXYZf(gmtl::Math::deg2Rad(-90.0f),0,0));

      mAnim = 0;
      mAnims.push_back("WALK");
      mAnims.push_back("RUN");
      mAnims.push_back("DANCE");
      mAnims.push_back("IDLE");
      mAnims.push_back("TYPE");
      mAnims.push_back("SIT");
      mAnims.push_back("WORK1");
      mAnims.push_back("WORK2");
   }

   ~AvatarState()
   {
      std::cout<<"Killing off AvatarState"<<std::endl;
   }

   void draw() const
   {
      glClearColor(0, 0, 1, 1);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(80.0f, 1024.0f/768.0f, 0.01f, 500.0f);

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glRotatef(gmtl::Math::deg2Rad(mRotX)*5.0f, 1,0,0);
      glRotatef(gmtl::Math::deg2Rad(mRotY)*5.0f, 0,1,0);

      glTranslatef(0, -5.0f, -5.0f);

//      glEnable(GL_TEXTURE_2D);
//      glEnable(GL_LIGHTING);
      glEnable(GL_DEPTH_TEST);

      mAvatar->render();
   }

   void update(float dt)
   {
      mAvatar->update(dt);
   }

   void onKeyPress(SDLKey sym, bool down)
   {
      if (down)
      {
         if (sym == SDLK_ESCAPE || sym == SDLK_q)
         {
            quit();
         }
         if (sym == SDLK_SPACE)
         {
            mAvatar->stopAnimation(mAnims[mAnim]);
            mAnim = (mAnim + 1) % mAnims.size();
            mAvatar->triggerAnimationCycle(mAnims[mAnim]);
         }
      }
   }

   void onMouseMove(int x, int y)
   {
      if (mIgnoreMouseMove)
      {
         mIgnoreMouseMove = false;
         return;
      }

      gmtl::Point2i center(getWidth() / 2, getHeight() / 2);
      gmtl::Point2i diff(x - center[0], y - center[1]);

      mRotX += diff[1];
      mRotY += diff[0];

      SDL_WarpMouse(center[0], center[1]);
      mIgnoreMouseMove = true;
   }

private:
   siren::Avatar* mAvatar;
   unsigned int mAnim;
   std::vector<std::string> mAnims;

   float mRotX;
   float mRotY;

   /// Do we need to ignore the next mouse move because of the mouse warp?
   bool mIgnoreMouseMove;
};

int main(int argc, char** argv)
{
   try
   {
      // Register the states
      new siren::StateCreatorImpl<AvatarState>("Avatar");

      std::auto_ptr<siren::Kernel> kernel(new siren::Kernel());
      kernel->start("Avatar");
   }
   catch(std::runtime_error& e)
   {
      std::cerr << "Caught Exception: " << e.what() << std::endl;
   }

   return 0;
}

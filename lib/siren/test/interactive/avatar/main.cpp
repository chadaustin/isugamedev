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
      : mBlurTexture(0)
      , mRotX(0.0f)
      , mRotY(0.0f)
      , mIgnoreMouseMove(true)
      , mFPS(0.0f)
      , mNumFrames(0)
      , mFrameTime(0.0f)
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

      std::cout << "Size in constructor: (" << getWidth() << ", " << getHeight() << ")" << std::endl;

      mBlurTexture = new siren::Texture(512, 512, 3, GL_RGB);
//      mBlurTexture = new siren::Texture(getWidth(), getHeight(), 3, GL_RGB);

      // init the GL state
      glEnable(GL_DEPTH_TEST);
      glEnable(GL_TEXTURE_2D);

      glClearColor(0, 0, 0, 1);
//      glClearAccum(0, 0, 0, 0);
//      glClear(GL_ACCUM_BUFFER_BIT);
   }

   ~AvatarState()
   {
      std::cout<<"Killing off AvatarState"<<std::endl;
      delete mBlurTexture;
   }

   void drawMotionBlur() const
   {
      glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         // Turn off depth testing so that we blend over the screen
         glDisable(GL_DEPTH_TEST);

         // Enable blending
         glBlendFunc(GL_SRC_ALPHA, GL_ONE);
         glEnable(GL_BLEND);

         // Decrease alpha value of the blend by 10% so that it will fade
         glColor4f(1, 1, 1, 0.95f);

         // Switch to an orthograhic view
         glMatrixMode(GL_PROJECTION);
         glPushMatrix();
            glLoadIdentity();
            gluOrtho2D(0, getWidth(), getHeight(), 0);

            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();

            // Blend the texture into the screen
            mBlurTexture->bind();
            glBegin(GL_QUADS);
               glTexCoord2f(0, 1); glVertex2f(0, 0);
               glTexCoord2f(0, 0); glVertex2f(0, getHeight());
               glTexCoord2f(1, 0); glVertex2f(getWidth(), getHeight());
               glTexCoord2f(1, 1); glVertex2f(getWidth(), 0);
            glEnd();
            mBlurTexture->unbind();
//            mBlurTexture->drawRectangle(0, 0, getWidth(), getHeight());

            glPopMatrix();
            glMatrixMode(GL_PROJECTION);

         // Switch back to the old projection
         glPopMatrix();
         glMatrixMode(GL_MODELVIEW);
      glPopAttrib();

      glEnable(GL_DEPTH_TEST);
      glDisable(GL_BLEND);
   }

   void draw() const
   {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(80.0f, (float)getWidth()/(float)getHeight(), 0.01f, 500.0f);

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      // Redraw the current blur texture
      glPushAttrib(GL_VIEWPORT_BIT);
         glViewport(0, 0, mBlurTexture->getTexWidth(), mBlurTexture->getTexHeight());
         drawMotionBlur();
         drawScene();

         // Copy the contents of the frame buffer into our blur texture
         mBlurTexture->bind();
         glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0,
                          mBlurTexture->getTexWidth(), mBlurTexture->getTexHeight(),
                          0);
         mBlurTexture->unbind();

         // Clear the frame buffer again
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glPopAttrib();
      glViewport(0, 0, getWidth(), getHeight());

      // Blend in the motion blur with the background color
      drawMotionBlur();

      drawScene();

      if (glGetError() != GL_NO_ERROR)
      {
         std::cerr << "I fucked up my GL State." << std::endl;
      }
   }

   void drawScene() const
   {
      glPushMatrix();
         glRotatef(gmtl::Math::deg2Rad(mRotX)*5.0f, 1,0,0);
         glRotatef(gmtl::Math::deg2Rad(mRotY)*5.0f, 0,1,0);

         glTranslatef(0, -5.0f, -5.0f);

         mAvatar->render();
      glPopMatrix();

//      glAccum(GL_ACCUM, 1.0);
//      glAccum(GL_MULT, 0.125);
//      glAccum(GL_RETURN, 1.0);
   }

   void update(float dt)
   {
      mAvatar->update(dt);

      ++mNumFrames;
      mFrameTime += dt;
      if (mFrameTime > 0.5f)
      {
         mFPS = (float)mNumFrames / mFrameTime;
         mFrameTime = 0.0f;
         mNumFrames = 0;
         std::cout << "FPS: " << mFPS << std::endl;
      }
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

   siren::Texture* mBlurTexture;

   float mRotX;
   float mRotY;

   /// Do we need to ignore the next mouse move because of the mouse warp?
   bool mIgnoreMouseMove;

   float mFPS;
   int   mNumFrames;
   float mFrameTime;
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

#include "GameScene.h"


namespace mw
{
   GameScene::GameScene()
   {
      mTexture = new Texture("images/ground.png");
   }

   GameScene::~GameScene()
   {
      delete mTexture;
   }

   void
   GameScene::draw()
   {
      const int size = 500;
      glPushMatrix();
         glRotatef(90, 1, 0, 0);
         glColor4f(1,1,1,1);
         mTexture->bind();
         glBegin(GL_QUADS);
         glTexCoord2f(0,  0);  glVertex2f(-size, -size);
         glTexCoord2f(0,  50); glVertex2f(-size,  size);
         glTexCoord2f(50, 50); glVertex2f(size,   size);
         glTexCoord2f(50, 0);  glVertex2f(size,  -size);
         mTexture->unbind();
         glEnd();
      glPopMatrix();
   }
}

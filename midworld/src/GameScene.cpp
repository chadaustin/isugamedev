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
      static cubeGeometry cube;

      const int size = 500;
      const int spacing = 10;
      const int spacing_2 = spacing / 2;
      glPushMatrix();
         glRotatef(90, 1, 0, 0);
         glColor4f(1,1,1,1);
         mTexture->bind();
         glBegin(GL_QUADS);
         glTexCoord2f(0,  0);  glVertex2f(-500, -500);
         glTexCoord2f(0,  50); glVertex2f(-500,  500);
         glTexCoord2f(50, 50); glVertex2f(500,   500);
         glTexCoord2f(50, 0);  glVertex2f(500,  -500);
         glEnd();
      glPopMatrix();

/*
      const float pillar_height = 0.5f;
      const float pillar_width = 0.4f;
      const int size_2 = 100 / 2;
      for (int x = -size_2; x < size_2; x += spacing)
      {
         for (int y = -size_2; y < size_2; y += spacing)
         {
            glPushMatrix();
            glTranslatef( (GLfloat)x, pillar_height, (GLfloat)y );
            glScalef( pillar_width, pillar_height, pillar_width );
            if (!(x == 0 && y == 0))
               cube.render();
            glPopMatrix();
         }
      }
*/
   }
}

#include <fstream>
#include <stdexcept>
#include "GameScene.h"


namespace mw
{
   std::istream& operator>>(std::ifstream& in, GameScene::Element& e)
   {
      return in >> e.x >> e.y >> e.z >> e.yaw >> e.pitch >> e.roll >> e.model;
   }

   GameScene::GameScene()
   {
      mGroundTexture = new Texture("images/ground.png");
   }

   GameScene::~GameScene()
   {
      delete mGroundTexture;
   }

   void
   GameScene::loadLevel(const std::string& filename)
   {
      std::ifstream level(filename.c_str());
      if (!level.is_open())
      {
         throw std::runtime_error("Could not open level: " + filename);
      }

      Element e;
      while (level >> e) {
         mElements.push_back(e);
      }
   }

   void
   GameScene::draw()
   {
      const int size = 500;
      glPushMatrix();
         glRotatef(90, 1, 0, 0);
         glColor4f(1,1,1,1);
         mGroundTexture->bind();
         glBegin(GL_QUADS);
            glTexCoord2f(0,  0);  glVertex2f(-size, -size);
            glTexCoord2f(0,  50); glVertex2f(-size,  size);
            glTexCoord2f(50, 50); glVertex2f(size,   size);
            glTexCoord2f(50, 0);  glVertex2f(size,  -size);
         glEnd();
         mGroundTexture->unbind();
      glPopMatrix();

      mSnowSystem.draw();
   }

   void
   GameScene::update(float dt)
   {
      mSnowSystem.update(dt);
   }
}

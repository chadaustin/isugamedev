/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************* midworld-cpr beg
 *
 * midworld - retro post-nuclear mayhem
 * midworld is (C) Copyright 2002 by
 *    Chad Austin, Josh Brown, Johnathan Gurley,
 *    Kevin Meinert, Andres Reinot, Ben Scott
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: GameState.cpp,v $
 * Date modified: $Date: 2002-12-21 19:25:49 $
 * Version:       $Revision: 1.134 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <SDL_opengl.h>
#include <gmtl/Generate.h>
#include <gmtl/QuatOps.h>

#include <loom/command.h>


#include "AmmoCrate.h"
#include "Application.h"
#include "AssaultRifle.h"
#include "BoundsSweepCollisionDetector.h"
#include "CollisionResponse.h"
#include "Enemy.h"
#include "EntityFactory.h"
#include "GameManager.h"
#include "GameState.h"
#include "InputManager.h"
#include "LevelLoader.h"
#include "MissileLauncher.h"
#include "NavNodeTree.h"
#include "OpenSGSceneViewer.h"
#include "Pistol.h"
#include "Shotgun.h"
#include "SpreadGun.h"
#include "StateFactory.h"
#include "StaticEntity.h"
#include "Testing.h"
#include "Turret.h"
#include "SkyDome.h"

namespace mw
{
   GameState::GameState(Application* app)
      : State(app)
      , mSpeed(10)
      , mPlayer(this)
      , mPlayerYawChange(0)
      , mIgnoreMouseMove(true)
   {
      // DO THIS FIRST!!!
      // Tell the EntityFactory to use this as the GameState
      EntityFactory::instance().setGameState(this);


      // Change the music as appropriate for gaming. :)
      Jukebox* jukebox = GameManager::instance().getSoundManager()->getJukebox();
      jukebox->clear();
      jukebox->addTrack("music/Theme001.ogg");
      jukebox->addTrack("music/Level001.ogg");
      jukebox->addTrack("music/Level002.ogg");
      jukebox->play();

      mScene = new Scene();
      OpenSGSceneViewer* viewer = new OpenSGSceneViewer(mScene);
      mSceneViewer = viewer;
      mScene->addSceneListener(viewer);

      // Init the collision detection system
      mCollDet = new BoundsSweepCollisionDetector();
      mCollDet->setSpatialIndex(viewer);

      // Init the physics engine
      mPhysics = new PhysicsEngine(mCollDet, new CollisionResponse(), mScene);

      add(&mPlayer);

      // Initialize the various game subsystems
      initializeInput();

      droidNavTree = new NavNodeTree();
      LevelLoader::process_xml("levels/level1.txt", this);

      //THis is the generation of the skydome
      GenerateDome(400.0f, 5.0f, 5.0f, 1.0f, 1.0f);
      mSkydomeTex = Texture::create("sky");
   
      /***********
       ***********
       animation init should be put somewhere else but for now we'll leaf it here
       ***********
       ***********/

      drawAni = true;
      // Animation initialization
      if (! mPlayerCoreModel.create("the player"))
      {
         std::cout << "failed to create mPlayerCoreModel!" << std::endl;
         throw std::runtime_error("failed to create mPlayerCoreModel!");
      }
      // load the core skeleton
      if (! mPlayerCoreModel.loadCoreSkeleton("animations/skeleton.csf"))
      {
         std::cout << "failed to load core skeleton!" << std::endl;
         throw std::runtime_error("failed to load core skeleton");
      }
      // load the material and animations
      walkingAnimationID = mPlayerCoreModel.loadCoreAnimation("animations/walk.caf");
      if (startWalkingAnimationID == -1 || walkingAnimationID == -1)
      {
         std::cout << "failed to load core animation file!" << std::endl;
         throw std::runtime_error("failed to load core animation file!");
      }

      // load the core mesh data
      meshID = mPlayerCoreModel.loadCoreMesh("animations/mesh.cmf");
      if (meshID == -1)
      {
         std::cout << "failed to load core mesh file!" << std::endl;
         throw std::runtime_error("failed to load core mesh file!");
      }

      //load the core material data
      hatMaterialID = mPlayerCoreModel.loadCoreMaterial("animations/mat.crf");
      if (hatMaterialID == -1)
      {
         std::cout << "failed to load core material data!" << std::endl;
         throw std::runtime_error("failed to load core material data!");
      }

      
      // create all the material threads
     const int BODY_MATERIAL_THREAD = 0;
      mPlayerCoreModel.createCoreMaterialThread(BODY_MATERIAL_THREAD);

      // assign a material for each material thread/set pair
      const int HAT_MATERIAL_SET = 0;
//      const int PANTS_MATERIAL_SET = 1;
//      const int COAT_MATERIAL_SET = 2;

      mPlayerCoreModel.setCoreMaterialId(BODY_MATERIAL_THREAD, HAT_MATERIAL_SET, hatMaterialID);
//      mPlayerCoreModel.setCoreMaterialId(BODY_MATERIAL_THREAD, COAT_MATERIAL_SET, coatMaterialID);
//      mPlayerCoreModel.setCoreMaterialId(BODY_MATERIAL_THREAD, PANTS_MATERIAL_SET, pantsMaterialID);

      
      if (! myModel.create(&mPlayerCoreModel))
      {
         std::cout << "Error creating model instance" << std::endl;
         throw std::runtime_error("Error creating model instance");
      }

      if (! myModel.attachMesh(meshID))
      {
         std::cout << "Error could not attach mesh!" << std::endl;
         throw std::runtime_error("Error could not attach mesh!");
      }

      myModel.setLodLevel(1.0f);
 //     myModel.setMaterialSet(PANTS_MATERIAL_SET);
      
      myModel.getMixer()->blendCycle(walkingAnimationID, 1.0f, 2.0f);

      pCalRenderer = myModel.getRenderer();
      
   }

   void
   GameState::update(float dt)
   {
      mPM.beginFrame();
      PMBlock block__(mPM, "update");
   
      AI.update();
      myModel.update(dt);
      mInputManager.update(dt);
      mSnowSystem.update(dt);
      
      
      mCamera.setTarget(mPlayer.getPos(), mPlayer.getRot());

      const gmtl::Vec3f accel  (0, 0, -mSpeed);
      const gmtl::Vec3f reverse(0, 0, mSpeed * 0.7f);
      const gmtl::Vec3f sleft  (mSpeed * -0.9f, 0, 0);
      const gmtl::Vec3f sright (mSpeed * 0.9f,  0, 0);

      const float camera_zoom_vel(10.0f);
      const float camera_pitch_vel(gmtl::Math::deg2Rad(100.0f));

      mPlayerVel += accel   * mActionUp->getEdgeState();
      mPlayerVel += reverse * mActionDown->getEdgeState();
      mPlayerVel += sleft   * mActionLeft->getEdgeState();
      mPlayerVel += sright  * mActionRight->getEdgeState();

      // set velocity of player based on the computed inputs
      mPlayer.setVel(mPlayer.getRot() * mPlayerVel);

      // Shoot
      if (mActionShoot->getEdgeState() == 1)
      {
         mPlayer.weapon().trigger(true);
      }
      else if (mActionShoot->getEdgeState() == -1)
      {
         mPlayer.weapon().trigger(false);
      }

      if (mActionCycleWeapon->getEdgeState() == 1)
      {
         mPlayer.nextWeapon();
      }

      // Camera zoom in
      if (mActionZoomIn->getEdgeState() == 1)
      {
         mCamera.setFollowDistanceVel(-camera_zoom_vel);
      }
      else if (mActionZoomIn->getEdgeState() == -1)
      {
         mCamera.setFollowDistanceVel(0);
      }
      // Camera zoom out
      if (mActionZoomOut->getEdgeState() == 1)
      {
         mCamera.setFollowDistanceVel(camera_zoom_vel);
      }
      else if (mActionZoomOut->getEdgeState() == -1)
      {
         mCamera.setFollowDistanceVel(0);
      }
      // Camera pitch down
      if (mActionPitchDown->getEdgeState() == 1)
      {
         mCamera.setPitchVel(camera_pitch_vel);
      }
      else if (mActionPitchDown->getEdgeState() == -1)
      {
         mCamera.setPitchVel(0);
      }
      // Camera pitch up
      if (mActionPitchUp->getEdgeState() == 1)
      {
         mCamera.setPitchVel(-camera_pitch_vel);
      }
      else if (mActionPitchUp->getEdgeState() == -1)
      {
         mCamera.setPitchVel(0);
      }

      if (mActionQuit->isActive())
      {
         invokeTransition("Menu");
         cleanUpCal3d();
      }

      // update player transform (using mouse-look)
      if (mPlayerYawChange != 0.0f)
      {
         // Update the player's rotation to match the new rotation
         gmtl::Quatf yaw_rot = gmtl::makeRot<gmtl::Quatf>(gmtl::AxisAnglef(
                                       mPlayerYawChange, gmtl::Vec3f(0,1,0)));
         mPlayer.setRot(mPlayer.getRot() * yaw_rot);

         // Reset the yaw change since we took care of it
         mPlayerYawChange = 0.0f;
      }


      // Reap dead entities
      reapDeadEntities();

      // Run the bodies through the physics simulator
      mPhysics->update(dt);

      // Iterate over all the entities and update them
//      Group* grp = mScene->getRoot();
      for (Scene::EntitySetCItr itr = mScene->begin(); itr != mScene->end(); ++itr)
      {
         // Allow the entity to update itself
         (*itr)->update(dt);
      }

      // Update the player and the camera
      mCamera.update(dt);
      mPlayer.update(dt);


      // if the player is below 300, he won!!
      if (mPlayer.getPos()[2] > 300)
      {
         invokeTransition("Ending");
         cleanUpCal3d();
      }
      
      mFPSCounter.update(dt);
   }
   gmtl::Vec3f temp;
   
   void GameState::draw()
   {
      PMBlock block__(mPM, "draw");
   
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
      glEnable(GL_DEPTH_TEST);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glDisable(GL_CULL_FACE);

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();

      /// @todo get rid of this...     maybe the clearing buffer too...
      gluPerspective(80.0f, 4.0f/3.0f, 0.01f, 3000.0f);

      // initialize your matrix stack used for transforming your models
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      glPushMatrix();
         mCamera.draw();

         mGameScene.draw();

         mSkydomeTex->bind();
         RenderSkyDome();
         mSkydomeTex->unbind();

         

         glTranslate(temp);
            if(drawAni && mActionUp) drawAnimation();
         glTranslate(-temp);
         

         // Make sure we clean up after OpenSG until they fix their bugs
         glPushAttrib(GL_ENABLE_BIT);
         {
            mSceneViewer->draw();
            // Grrr... OpenSG leaves the current texture bound
            glBindTexture(GL_TEXTURE_2D, 0);
         }
         glPopAttrib();
         

         drawEntities();
         
         
         // Draw this last for correct depth testing
         mSnowSystem.draw();

         
         
//         drawBounds();
      glPopMatrix();

      mHUD.draw(application().getWidth(), application().getHeight(),
                mPlayer, mFPSCounter.getFPS(), mPM.getOutput());
   }
   
   void
   GameState::drawEntities()
   {
      // Run through the entities in the scene and mark those that are dead
      for (Scene::EntitySetCItr itr = mScene->begin(); itr != mScene->end(); ++itr)
      {
         const Entity* entity = *itr;
         glTranslate(entity->getPos());
         if(entity == &mPlayer)
         {
            temp = entity->getPos();
            entity->draw();
         }
         glTranslate(-entity->getPos());
      }
   }


   void 
   GameState::drawAnimation()
   {
      glPushMatrix();
      glPushAttrib(GL_ALL_ATTRIB_BITS);
      glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT );
      
      gmtl::Quatf playerRot;
      gmtl::Vec3f tempPos;
      
      gmtl::Matrix44f mat = gmtl::make<gmtl::Matrix44f>(mPlayer.getRot());
      glMultMatrixf(mat.getData());

      
      
      tempPos = mPlayer.getPos();
      playerRot = mPlayer.getRot();
          
      
      if(!pCalRenderer->beginRendering())
      {
         std::cout << "not able to begin rendering" << std::endl;
      }else
      {
         glPushMatrix();
           
          glRotatef(270, 1,0,0);
          glRotatef(180, 0,0,1);
          glScalef(0.008f, 0.008f, 0.008f);
          
            // set global OpenGL states
          glEnable(GL_DEPTH_TEST);
          glShadeModel(GL_SMOOTH);
          glEnable(GL_LIGHTING);
          glEnable(GL_LIGHT0);

          // we will use vertex arrays, so enable them
          glEnableClientState(GL_VERTEX_ARRAY);
          glEnableClientState(GL_NORMAL_ARRAY);

          // get the number of meshes
          int meshCount;
          meshCount = pCalRenderer->getMeshCount();

          // render all meshes of the model
          int meshId;
          for(meshId = 0; meshId < meshCount; meshId++)
          {
            // get the number of submeshes
            int submeshCount;
            submeshCount = pCalRenderer->getSubmeshCount(meshId);

            // render all submeshes of the mesh
            int submeshId;
            for(submeshId = 0; submeshId < submeshCount; submeshId++)
            {
              // select mesh and submesh for further data access
              if(pCalRenderer->selectMeshSubmesh(meshId, submeshId))
              {
                unsigned char meshColor[4];
                GLfloat materialColor[4];

                // set the material ambient color
                pCalRenderer->getAmbientColor(&meshColor[0]);
                materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
                glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);

                // set the material diffuse color
                pCalRenderer->getDiffuseColor(&meshColor[0]);
                materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
                glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);

                // set the material specular color
                pCalRenderer->getSpecularColor(&meshColor[0]);
                materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
                glMaterialfv(GL_FRONT, GL_SPECULAR, materialColor);

                // set the material shininess factor
                float shininess;
                shininess = pCalRenderer->getShininess();
                glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

                // get the transformed vertices of the submesh
                static float meshVertices[30000][3];
                int vertexCount;
                vertexCount = pCalRenderer->getVertices(&meshVertices[0][0]);

                // get the transformed normals of the submesh
                static float meshNormals[30000][3];
                pCalRenderer->getNormals(&meshNormals[0][0]);

                // get the texture coordinates of the submesh
                static float meshTextureCoordinates[30000][2];
                int textureCoordinateCount;
                textureCoordinateCount = pCalRenderer->getTextureCoordinates(0, &meshTextureCoordinates[0][0]);

                // get the faces of the submesh
                static CalIndex meshFaces[50000][3];
                int faceCount;
                faceCount = pCalRenderer->getFaces(&meshFaces[0][0]);

                
                // set the vertex and normal buffers
                glVertexPointer(3, GL_FLOAT, 0, &meshVertices[0][0]);
                glNormalPointer(GL_FLOAT, 0, &meshNormals[0][0]);

                // set the texture coordinate buffer and state if necessary
                if((pCalRenderer->getMapCount() > 0) && (textureCoordinateCount > 0))
                {
                  glEnable(GL_TEXTURE_2D);
                  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                  glEnable(GL_COLOR_MATERIAL);

                  // set the texture id we stored in the map user data
                  glBindTexture(GL_TEXTURE_2D, (GLuint)pCalRenderer->getMapUserData(0));

                  // set the texture coordinate buffer
                  glTexCoordPointer(2, GL_FLOAT, 0, &meshTextureCoordinates[0][0]);
                  glColor3f(1.0f, 1.0f, 1.0f);
                }

                // draw the submesh
              
              if(sizeof(CalIndex)==2)
                 glDrawElements(GL_TRIANGLES, faceCount * 3, GL_UNSIGNED_SHORT, &meshFaces[0][0]);
              else
                 glDrawElements(GL_TRIANGLES, faceCount * 3, GL_UNSIGNED_INT, &meshFaces[0][0]);

                // disable the texture coordinate state if necessary
                if((pCalRenderer->getMapCount() > 0) && (textureCoordinateCount > 0))
                {
                  glDisable(GL_COLOR_MATERIAL);
                  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                  glDisable(GL_TEXTURE_2D);
                }
            }
         }
            glPopMatrix();
      }

      // clear vertex array state
      glDisableClientState(GL_NORMAL_ARRAY);
      glDisableClientState(GL_VERTEX_ARRAY);

      // clear light
      glDisable(GL_LIGHTING);
      glDisable(GL_LIGHT0);
      glDisable(GL_DEPTH_TEST);

      // end the rendering
      pCalRenderer->endRendering();
      }
      
      glPopAttrib();
      glPopClientAttrib();
      
      glPopMatrix();
   }
   
   void
   GameState::drawBounds()
   {
      // Draw the bounds
      glColor4f(1,0,0,1);
      for (Scene::EntitySetCItr itr = mScene->begin(); itr != mScene->end(); ++itr)
      {
         const Entity* entity = *itr;
         const gmtl::AABoxf& bounds = entity->getBounds();
         const gmtl::Point3f& min = bounds.getMin();
         const gmtl::Point3f& max = bounds.getMax();

         // Front face
         glBegin(GL_LINE_LOOP);
            glVertex3f(min[0], min[1], min[2]);
            glVertex3f(max[0], min[1], min[2]);
            glVertex3f(max[0], max[1], min[2]);
            glVertex3f(min[0], max[1], min[2]);
         glEnd();

         // Back face
         glBegin(GL_LINE_LOOP);
            glVertex3f(min[0], min[1], max[2]);
            glVertex3f(max[0], min[1], max[2]);
            glVertex3f(max[0], max[1], max[2]);
            glVertex3f(min[0], max[1], max[2]);
         glEnd();

         // Bottom face
         glBegin(GL_LINE_LOOP);
            glVertex3f(min[0], min[1], min[2]);
            glVertex3f(max[0], min[1], min[2]);
            glVertex3f(max[0], min[1], max[2]);
            glVertex3f(min[0], min[1], max[2]);
         glEnd();

         // Top face
         glBegin(GL_LINE_LOOP);
            glVertex3f(min[0], max[1], min[2]);
            glVertex3f(max[0], max[1], min[2]);
            glVertex3f(max[0], max[1], max[2]);
            glVertex3f(min[0], max[1], max[2]);
         glEnd();
      }
   }

   void
   GameState::onKeyPress(SDLKey sym, bool down)
   {
      mInputManager.onKeyPress(sym, down);
   }

   void
   GameState::onMousePress(Uint8 button, bool down, int /*x*/, int /*y*/)
   {
      mInputManager.onMousePress(button, down);
   }

   void
   GameState::onMouseMove(int x, int y)
   {
      if (mIgnoreMouseMove)
      {
         mIgnoreMouseMove = false;
         return;
      }

      // Calculate the change in yaw
      gmtl::Point2f wnd_center((float)application().getWidth() / 2.0f,
                               (float)application().getHeight() / 2.0f);
      float yaw = -(float)(x - wnd_center[0]) / 180.0f;
      mPlayerYawChange += yaw;

      // Warp the mouse back to the center of the screen
      SDL_WarpMouse((int)wnd_center[0], (int)wnd_center[1]);
      mIgnoreMouseMove = true;
   }

   void GameState::reapDeadEntities()
   {
      typedef std::list<Entity*> DeadList;
      DeadList dead;

      // Run through the entities in the scene and mark those that are dead
      for (Scene::EntitySetItr itr = mScene->begin(); itr != mScene->end(); ++itr)
      {
         Entity* entity = *itr;
         if (entity->isExpired())
         {
            dead.push_back(entity);
         }
      }

      // Remove all entities marked as dead
      for (DeadList::iterator itr = dead.begin(); itr != dead.end(); ++itr)
      {
         Entity* entity = *itr;
         mScene->remove(entity);
         NodeMap::iterator i=mMap.find(entity);
         // if it's an ai node remove it from the ai system
         if(i!=mMap.end())
         {
            AI.unregisterNode(i->second->getName());
         }


         if (entity == &mPlayer)
         {
            // if the player is dead, it's Game Over
            invokeTransition("GameOver");
            cleanUpCal3d();
         }
         else
         {
            delete entity;
         }
      }
   }

   void GameState::cleanUpCal3d()
   {
      drawAni=false;
      myModel.destroy();
      mPlayerCoreModel.destroy();
   }

   void GameState::add(Entity* entity)
   {
      mScene->add(entity);
   }

   void GameState::addSmart(Entity* entity, lm::aiNode *node)
   {
      add(entity);
      AI.registerNode(node);
      mMap[entity] = node;
   }

   void
   GameState::addNavNode(Node* node)
   {
      droidNavTree->addNode(node);
      droidNavTree->getTree().size();
   }

   void
   GameState::addNavNodeLink(std::string n1, std::string n2)
   {
      droidNavTree->addLink(n1, n2);
   }

   void GameState::initializeInput()
   {
      mInputManager.loadMappings("inputmap.cfg");
      mActionUp          = mInputManager.getAction("MOVE UP");
      mActionDown        = mInputManager.getAction("MOVE DOWN");
      mActionRight       = mInputManager.getAction("MOVE RIGHT");
      mActionLeft        = mInputManager.getAction("MOVE LEFT");
      mActionQuit        = mInputManager.getAction("QUIT");
      mActionZoomIn      = mInputManager.getAction("ZOOM IN");
      mActionZoomOut     = mInputManager.getAction("ZOOM OUT");
      mActionPitchUp     = mInputManager.getAction("PITCH UP");
      mActionPitchDown   = mInputManager.getAction("PITCH DOWN");
      mActionYawLeft     = mInputManager.getAction("YAW LEFT");
      mActionYawRight    = mInputManager.getAction("YAW RIGHT");
      mActionShoot       = mInputManager.getAction("SHOOT");
      mActionCycleWeapon = mInputManager.getAction("CYCLE WEAPON");
   }

   /**
    * this function sets up the turret object in the game, assigns it all the
    * ai related stuff that it needs and returns a reference to the droid.
    * TODO: figure out how to handle the parent case.
    */
   Droid*
   GameState::setupDroid(const std::string& name, const std::string& parent,
                         int maxChild, int level, NavNodeTree& tree)
   {
      lm::aiNode* node1 = new lm::aiNode(name, NULL, maxChild, level);
      mAInodes.push_back(node1);

      Droid* droid = EntityFactory::instance().create<Droid>();
      
      
      // setup the shoot reflex
      myTestCommand = new droidTesting(droid, &mPlayer);
      shootCommand = new droidCommand(droid, &mPlayer);

      second = new lm::behavior;
      
      second->addCommand(shootCommand);
      node2Instinct = new lm::reflex(node1, second, myTestCommand);
      
      // setup the fucked reflex
      fukedTest = new droidFuckedTesting(droid);
      fuckedCommand = new droidFuckedCommand(droid, droidNavTree);
      fuckedBehavior = new lm::behavior;

      fuckedBehavior->addCommand(fuckedCommand);
      droidFuked = new lm::reflex(node1, fuckedBehavior, fukedTest);

      // setup the Goal reflex
      goalTest = new droidChooseNewNodeTesting(droid, droidNavTree);
      goalCommand = new droidFindCloseNodeCommand(droid, droidNavTree);
      goalBehavior = new lm::behavior;

      goalBehavior->addCommand(goalCommand);
      atGoalNode = new lm::reflex(node1, goalBehavior, goalTest);

      // setup the last reflex which is the defualt (always called reflex)
      moveCommand = new droidMoveToNodeCommand(droid, droidNavTree);
      moveBehavior = new lm::behavior;
      moveTest = new tests();

      moveBehavior->addCommand(moveCommand);
      defaultDroidAction = new lm::reflex(node1, moveBehavior, moveTest);

      droid->setTree(droidNavTree);
      
      AI.registerNode(node1);

      mMap[droid] = node1;

      return droid;
   }


   /**
    * This function sets up the turret object in the game, assigns it all the ai
    * related stuff that it needs and returns a reference to that Turret.
    * TODO: figure out how to handle the parent case.
    */
   Turret*
   GameState::setupTurret(const std::string& name, const std::string& parent,
                          int maxChild, int level)
   {
      lm::aiNode* node1 = new lm::aiNode(name, NULL, maxChild, level);
      mAInodes.push_back(node1);

      Turret* turret = EntityFactory::instance().create<Turret>();
 
//      node1sCommand = new lm::simpleCommand<Turret>(turret, &Turret::aim);

      first = new lm::behavior;

      
      aimTestCommand = new turretTesting(turret, &mPlayer);
      aimCommand = new turretCommand(turret, &mPlayer);

      first->addCommand(aimCommand);
      
      
      node1Instinct = new lm::reflex(node1, first, aimTestCommand);
      AI.registerNode(node1);

      mMap[turret] = node1;
      return turret;
   }
}

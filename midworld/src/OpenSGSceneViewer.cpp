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
 * File:          $RCSfile: OpenSGSceneViewer.cpp,v $
 * Date modified: $Date: 2002-09-18 00:30:39 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <SDL_opengl.h>
#include <gmtl/External/OpenSGConvert.h>
#ifdef WIN32  // OpenSG needs Winsock  :(:(:(
#include <winsock.h>
#endif
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGMatrixUtility.h>
#include <OpenSG/OSGDirectionalLight.h>
#include "OpenSGSceneViewer.h"
#include "GameManager.h"

namespace mw
{
   OpenSGSceneViewer::OpenSGSceneViewer(Scene* scene)
      : mScene(scene)
   {
      osg::osgInit(0,0);

      mRenderAction = osg::RenderAction::create();
      mWin = osg::PassiveWindow::create();
      mViewport = osg::PassiveViewport::create();
      mBackground = osg::PassiveBackground::create();
      mCamera = osg::MatrixCamera::create();

      // setup the camera
      osg::Matrix proj_matrix, modelview_matrix;
      osg::MatrixPerspective(proj_matrix, 80.0f, 4.0f/3.0f, 0.01f, 10000.0f);
      osg::beginEditCP(mCamera);
         mCamera->setNear(0.1);
         mCamera->setFar(10000.0);
         mCamera->setProjectionMatrix(proj_matrix);
         mCamera->setModelviewMatrix(modelview_matrix);
      osg::endEditCP(mCamera);

      // setup the viewport
      osg::beginEditCP(mViewport);
         mViewport->setLeft(0);
         mViewport->setRight(1);
         mViewport->setBottom(1);
         mViewport->setTop(0);
         mViewport->setCamera(mCamera);
         mViewport->setBackground(mBackground);
      osg::endEditCP(mViewport);

      // setup the window
      osg::beginEditCP(mWin);
         mWin->addPort(mViewport);
      osg::endEditCP(mWin);

      // init OpenSG's GL state
      mWin->init();

      // Create the root node
      mSceneRoot = osg::Node::create();
      mSceneTransform = osg::Transform::create();
      osg::beginEditCP(mSceneRoot, osg::Node::CoreFieldMask);
         mSceneRoot->setCore(mSceneTransform);
      osg::endEditCP(mSceneRoot, osg::Node::CoreFieldMask);

      // XXX: make the top level node a light source for now
      osg::DirectionalLightPtr light = osg::DirectionalLight::create();
      light->setDirection(0,1,0);
      osg::NodePtr lightNode = osg::Node::create();
      osg::beginEditCP(lightNode, osg::Node::CoreFieldMask | osg::Node::ChildrenFieldMask);
         lightNode->setCore(light);
         lightNode->addChild(mSceneRoot);
      osg::endEditCP(lightNode, osg::Node::CoreFieldMask | osg::Node::ChildrenFieldMask);

      // Add the root node to the viewport
      osg::beginEditCP(mViewport, osg::Node::ChildrenFieldMask);
         mViewport->setRoot(lightNode);
      osg::endEditCP(mViewport, osg::Node::ChildrenFieldMask);
   }

   OpenSGSceneViewer::~OpenSGSceneViewer()
   {
   }

   void OpenSGSceneViewer::draw()
   {
      // XXX: Refactor this update into an event-based system
      for (EntityNodeMap::iterator itr = mEntityNodeMap.begin();
           itr != mEntityNodeMap.end(); ++itr)
      {
         const Entity::UID& uid = itr->first;
         Entity* entity = mScene->get(uid);
         if (entity != 0)
         {
            // Compute the xform matrix for the entity
            const gmtl::Point3f& pos = entity->getPos();
            const gmtl::Quatf& rot = entity->getRot();
            gmtl::Matrix44f xform = gmtl::makeTrans<gmtl::Matrix44f>(static_cast<gmtl::Vec3f>(pos));
            xform *= gmtl::make<gmtl::Matrix44f>(rot);
//            gmtl::Matrix44f xform = gmtl::make<gmtl::Matrix44f>(rot);
//            xform *= gmtl::makeTrans<gmtl::Matrix44f>(static_cast<gmtl::Vec3f>(pos));

            // Convert the matrix to OpenSG matrix
            osg::Matrix osg_mat;
            gmtl::set(osg_mat, xform);

            // Update the node for the entity
            osg::NodePtr node = itr->second;
            osg::TransformPtr trans = osg::TransformPtr::dcast(node->getCore());
            osg::beginEditCP(trans, osg::Transform::MatrixFieldMask);
            {
               trans->setMatrix(osg_mat);
            }
            osg::endEditCP(trans, osg::Transform::MatrixFieldMask);
         }
      }

      // OpenSG likes to modify the viewport and not change it back :(
      glPushAttrib(GL_VIEWPORT_BIT);
         // init this frame
         mWin->frameInit();

         float modelview[16];
         float projection[16];
         glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)modelview);
         glGetFloatv(GL_PROJECTION_MATRIX, (GLfloat*)projection);

         osg::Matrix4f mv_mat, proj_mat;
         mv_mat.setValue((GLfloat*)modelview);
         proj_mat.setValue((GLfloat*)projection);

         // Setup the camera
         osg::beginEditCP(mCamera);
            mCamera->setProjectionMatrix(proj_mat);
            mCamera->setModelviewMatrix(mv_mat);
         osg::endEditCP(mCamera);

         // Do the draw action. Push matrices on the stack so the rest of the app
         // is not affected by the changes made by OpenSG.
         glMatrixMode(GL_PROJECTION);
         glPushMatrix();
         glMatrixMode(GL_MODELVIEW);
         glPushMatrix();

         mWin->render(mRenderAction);

         glPopMatrix();
         glMatrixMode(GL_PROJECTION);
         glPopMatrix();
         glMatrixMode(GL_MODELVIEW);

         // finish up the frame
         mWin->frameExit();
      glPopAttrib();
   }

   void OpenSGSceneViewer::entityAdded(const SceneEvent& evt)
   {
      Entity* entity = evt.getEntity();

      ResourceManager* res_mgr = GameManager::instance().getResourceManager();
      const std::string& model = res_mgr->get(entity->getModel());
      osg::NodePtr model_node = GameManager::instance().getModelManager()->get(model);     

      // Create a parent transform node for the model
      osg::NodePtr trans_node = osg::Node::create();
      osg::TransformPtr trans = osg::Transform::create();

      // Add the model node to the transform node
      osg::beginEditCP(trans_node, osg::Node::CoreFieldMask | osg::Node::ChildrenFieldMask);
         trans_node->setCore(trans);
         trans_node->addChild(model_node);
      osg::endEditCP(trans_node, osg::Node::CoreFieldMask | osg::Node::ChildrenFieldMask);

      // Add the transform node (with model) to the scene
      osg::beginEditCP(mSceneRoot, osg::Node::ChildrenFieldMask);
         mSceneRoot->addChild(trans_node);
      osg::endEditCP(mSceneRoot);

      // Cache a mapping of the entity UID to its transform node
      mEntityNodeMap[entity->getUID()] = trans_node;

//      std::cout<<"Added entity: uid="<<entity->getUID()<<std::endl;
   }

   void OpenSGSceneViewer::entityRemoved(const SceneEvent& evt)
   {
      const Entity::UID& uid = evt.getEntity()->getUID();

      EntityNodeMap::iterator itr = mEntityNodeMap.find(uid);
      if (itr != mEntityNodeMap.end())
      {
         // Remove the entity node from its parent
         osg::NodePtr entity_node = itr->second;
         osg::NodePtr parent = entity_node->getParent();
         osg::beginEditCP(parent, osg::Node::ChildrenFieldMask);
            parent->subChild(entity_node);
         osg::endEditCP(parent, osg::Node::ChildrenFieldMask);

         // Remove the entity UID to node ptr mapping
         mEntityNodeMap.erase(itr);

//         std::cout<<"Removed entity: uid="<<uid<<std::endl;
      }
      else
      {
         std::cerr<<"Couldn't remove unknown entity: uid="<<uid<<std::endl;
      }
   }
}
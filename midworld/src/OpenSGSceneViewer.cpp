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
 * Date modified: $Date: 2003-05-01 05:10:08 $
 * Version:       $Revision: 1.22 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <list>
#include <SDL_opengl.h>

// GMTL
#include <gmtl/External/OpenSGConvert.h>
#include <gmtl/Containment.h>
#include <gmtl/Output.h>

// OpenSG
#ifdef WIN32  // OpenSG needs Winsock  :(:(:(
#include <winsock.h>
#endif
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGMatrixUtility.h>
#include <OpenSG/OSGDirectionalLight.h>
#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGSceneFileHandler.h>

#include "OpenSGSceneViewer.h"
#include "ResourceManager.h"

namespace mw
{
   /// This class initializes OpenSG before main() is entered
   class InitOpenSG
   {
   public:
      InitOpenSG()
      {
         osg::osgInit(0, 0);

         typedef std::list<const char*> SuffixList;
         SuffixList suffixes;
         osg::SceneFileHandler::the().getSuffixList(suffixes);

         std::cout<<"Scenegraph file formats supported:"<<std::endl;
         for(SuffixList::iterator itr = suffixes.begin(); itr != suffixes.end(); ++itr)
         {
            std::cout<<"\t"<<(*itr)<<std::endl;
         }
      }
   };

   static InitOpenSG initOpenSG;
   
   /**
    * The ResourceManager CachePolicy for osg::NodePtr objects.
    * XXX: HACK - This code is duplicated in LoadState.cpp
    */
   template<>
   struct CachePolicy<osg::NodePtr>
   {
      static osg::NodePtr copy(osg::NodePtr cacheVal)
      {
         return osg::cloneTree(cacheVal);
      }

      static osg::NodePtr create(const std::string& name)
      {
         return osg::SceneFileHandler::the().read(name.c_str());
      }

      static void destroy(osg::NodePtr& val)
      {
         // do nothing ... osg::NodePtrs are ref counted
      }
   };


   OpenSGSceneViewer::OpenSGSceneViewer(Scene* scene)
      : mScene(scene)
   {
      // this is called in ModelManager's constructor
//      osg::osgInit(0,0);

      mRenderAction = osg::RenderAction::create();
      mWin = osg::PassiveWindow::create();
      mViewport = osg::PassiveViewport::create();
      mBackground = osg::PassiveBackground::create();
      mCamera = osg::MatrixCamera::create();

      // setup the camera
      osg::Matrix proj_matrix, modelview_matrix;
      osg::MatrixPerspective(proj_matrix, 80.0f, 4.0f/3.0f, 0.01f, 3000.0f);
      osg::beginEditCP(mCamera);
         mCamera->setNear(0.1);
         mCamera->setFar(3000.0);
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

   void
   OpenSGSceneViewer::draw()
   {
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

    //     glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
         glEnable(GL_CULL_FACE);
    //     glDisable(GL_DEPTH_TEST);
         glDisable(GL_BLEND);
         mWin->render(mRenderAction);

         glPopMatrix();
         glMatrixMode(GL_PROJECTION);
         glPopMatrix();
         glMatrixMode(GL_MODELVIEW);

         // finish up the frame
         mWin->frameExit();
      glPopAttrib();

//      drawBounds();
   }

   std::list<RigidBody*>
   OpenSGSceneViewer::intersect(const gmtl::AABoxf& region)
   {
      //XXX: Actually traverse the graph so we get O(log n) performance rather
      //     than this crappy O(n) algorithm.
      std::list<RigidBody*> matches;

      for (EntityNodeMap::iterator itr = mEntityNodeMap.begin();
           itr != mEntityNodeMap.end(); ++itr)
      {
         /*
         osg::NodePtr entity_node = itr->second;

         // Get the bounds of this node
         osg::Pnt3f min, max;
         entity_node->getVolume().getBounds(min, max);
         gmtl::Point3f gmtl_min(min[0], min[1], min[2]);
         gmtl::Point3f gmtl_max(max[0], max[1], max[2]);
         gmtl::AABoxf entity_bounds(gmtl_min, gmtl_max);
         */

         // Compare this node's bounds to the search bounds
         if (gmtl::isInVolume(region, itr->first->getBounds()))
         {
            matches.push_back(itr->first);
         }
      }

      return matches;
   }

   void
   OpenSGSceneViewer::entityAdded(const SceneEvent& evt)
   {
      Entity* entity = evt.getEntity();
      std::cout << "[OpenSGSceneViewer] Adding entity: " << entity << std::endl;

      ResourceManager& resmgr = ResourceManagerSingleton::instance();
      osg::NodePtr model_node = resmgr.get<osg::NodePtr>(entity->getModel());

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
      mEntityNodeMap[entity] = trans_node;
      entity->addBodyChangeListener(this);

      updateEntity(entity);

      // Setup the entity's bounds
      trans_node->updateVolume();
      gmtl::AABoxf bounds(getBounds(entity));
      entity->setBoundsSize(bounds.getMax() - bounds.getMin());



//      std::cout<<"Added entity: uid="<<entity->getUID()<<std::endl;
   }

   void
   OpenSGSceneViewer::entityRemoved(const SceneEvent& evt)
   {
      Entity* entity = evt.getEntity();

      EntityNodeMap::iterator itr = mEntityNodeMap.find(entity);
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

         // Stop listening to the entity
         evt.getEntity()->removeBodyChangeListener(this);

//         std::cout<<"Removed entity: uid="<<uid<<std::endl;
      }
      else
      {
         std::cerr << "Couldn't remove unknown entity: entity=" << entity << std::endl;
      }
   }

   void
   OpenSGSceneViewer::bodyChanged(const BodyChangeEvent& evt)
   {
      Entity* entity = dynamic_cast<Entity*>(evt.getSource());

      if (!entity)
      {
         return;
      }

      updateEntity(entity);
   }

   void
   OpenSGSceneViewer::updateEntity(Entity* entity)
   {
      // Update the scene graph to reflect the change in the entity

      // Compute the xform matrix for the entity
      const gmtl::Point3f& pos = entity->getPos();
      const gmtl::Quatf& rot = entity->getRot();
      gmtl::Matrix44f xform = gmtl::makeTrans<gmtl::Matrix44f>(static_cast<gmtl::Vec3f>(pos));
      xform *= gmtl::make<gmtl::Matrix44f>(rot);

      gmtl::Matrix44f scaleMat;
      gmtl::setScale(scaleMat, entity->getScale());
      xform *= scaleMat;

      // Convert the matrix to OpenSG matrix
      osg::Matrix osg_mat;
      gmtl::set(osg_mat, xform);

      // Update the node for the entity
      osg::NodePtr node = mEntityNodeMap[entity];
      osg::TransformPtr trans = osg::TransformPtr::dcast(node->getCore());
      osg::beginEditCP(trans, osg::Transform::MatrixFieldMask);
      {
         trans->setMatrix(osg_mat);
      }
      osg::endEditCP(trans, osg::Transform::MatrixFieldMask);

      // Make sure OpenSG's volume for this entity is valid for further
      // processing this frame.
      node->updateVolume();

      // Update the entity's bounds

      // bounds from OpenSG
      gmtl::AABoxf bounds(getBounds(entity));
      gmtl::Vec3f midpoint = (bounds.getMin() + bounds.getMax()) / 2;

      // entity bounds
      gmtl::Vec3f size(entity->getBoundsSize());

      entity->setBounds(gmtl::AABoxf(
                           midpoint - size / 2,
                           midpoint + size / 2));
   }

   gmtl::AABoxf
   OpenSGSceneViewer::getBounds(Entity* entity)
   {
      osg::Pnt3f min, max;
      mEntityNodeMap[entity]->getVolume().getBounds(min, max);
      gmtl::Point3f gmtl_min(min[0], min[1], min[2]);
      gmtl::Point3f gmtl_max(max[0], max[1], max[2]);
      return gmtl::AABoxf(gmtl_min, gmtl_max);
   }

   void
   OpenSGSceneViewer::drawBounds()
   {
      // Draw the goddamn bounding boxes
      for (EntityNodeMap::iterator itr = mEntityNodeMap.begin();
           itr != mEntityNodeMap.end(); ++itr)
      {
         osg::NodePtr entity_node = itr->second;

         // Get the bounds of this node
         osg::Pnt3f osg_min, osg_max;
         entity_node->getVolume().getBounds(osg_min, osg_max);
         gmtl::Point3f min(osg_min[0], osg_min[1], osg_min[2]);
         gmtl::Point3f max(osg_max[0], osg_max[1], osg_max[2]);

         glColor4f(0,0,1,1);
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
}

/************************************************************** brotha-head beg
 *
 * Warn-a-Brotha
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Josh Carlson <josh@chegg.com>
 *    Jeremy Hanson <jjhanson@iastate.edu>
 *    Chad Okere <cokere@hatori42.com>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Scene.cpp,v $
 * Date modified: $Date: 2002-04-24 10:59:40 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 *********************************************************** brotha-head-end */
/*************************************************************** brotha-cpr beg
 *
 * Warn-a-Brotha
 * Warn-a-Brotha is (C) Copyright 2002 by
 *    Chad Austin, Josh Carlson, Jeremy Hanson, Chad Okere, Ben Scott
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
 ************************************************************ brotha-cpr-end */
#include "Scene.h"
#include <osgDB/ReadFile>

namespace client {
   Scene::Scene()
      : mFollowDist(1500)
      , mFollowPitch(0.40)
      , mTargetRot(0,0,0,1)
      , mTargetPos(0,0,0)
      , mCurRot(0,0,0,1)
      , mCurPos(0,0,-30)
   {
      // Setup our SceneView
      mSceneView = new osgUtil::SceneView();
      mSceneView->setDefaults();
      mSceneView->setBackgroundColor(osg::Vec4(0,0,0,0));
      mSceneView->getLight()->setAmbient(osg::Vec4(0.3f,0.3f,0.3f,1.0f));
      mSceneView->getLight()->setDiffuse(osg::Vec4(0.9f,0.9f,0.9f,1.0f));
      mSceneView->getLight()->setSpecular(osg::Vec4(1.0f,1.0f,1.0f,1.0f));

      mRoot = new osg::Group();

      // Camera follow node
      mFollowView = new osg::Transform();
      osg::Matrix mat = osg::Matrix::rotate(mFollowPitch, 1,0,0) *
                        osg::Matrix::translate(0,0,-mFollowDist);
      mFollowView->setMatrix(mat);
      mRoot->addChild(mFollowView);

      // Camera target view node
      mFollowTarget = new osg::Transform();
      mFollowView->addChild(mFollowTarget);
      
      mObjs = new osg::Group();
      mStaticObjs = new osg::Group();
      mFollowTarget->addChild(mObjs);
      mFollowTarget->addChild(mStaticObjs);

      // Tell our scene viewer about our scene
      mSceneView->setSceneData(mRoot);
   }

   Scene::~Scene()
   {}

   void Scene::draw()
   {
      mSceneView->app();
      mSceneView->cull();
      mSceneView->draw();
   }

   void Scene::addObject(const std::string& name, const std::string& model)
   {
      // Try to get the model from the model manager
      osg::Node* modelNode = NULL;
      try {
         modelNode = mModelMgr.get(model);
      } catch (std::exception& e) {
         std::cerr<<"Failed to load model "<<model<<" for "<<name<<": "<<e.what()<<std::endl;
         return;
      }

      // Add a transform node on top of the model so we can control it
      osg::Transform* modelTrans = new osg::Transform();
      modelTrans->addChild(modelNode);
      modelTrans->setName(name);

      // Add our new model to the scene
      mObjs->addChild(modelTrans);
   }

   void Scene::removeObject(const std::string& name)
   {
      for (int i=0; i<mObjs->getNumChildren(); ++i) {
         osg::Node* node = mObjs->getChild(i);
         if (node->getName() == name) {
            mObjs->removeChild(node);
            return;
         }
      }
   }

   osg::Transform* Scene::getObject(const std::string& name)
   {
      for (int i=0; i<mObjs->getNumChildren(); ++i) {
         osg::Node* node = mObjs->getChild(i);
         if (node->getName() == name) {
            return (osg::Transform*)node;
         }
      }
      return NULL;
   }

   osg::Transform* Scene::getView()
   {
      return mFollowView;
   }
}

/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
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
 * File:          $RCSfile: Scene.h,v $
 * Date modified: $Date: 2002-05-03 07:18:33 $
 * Version:       $Revision: 1.5 $
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
#ifndef CLIENT_SCENE_H
#define CLIENT_SCENE_H

#include <osg/Vec3>
#include <osg/Matrix>
#include <osg/Transform>
#include <osgUtil/SceneView>
#include "ModelManager.h"
#include "Camera.h"
#include "game/Object.h"

namespace client {
   /**
    * Manages our scene. The scene is initially set up as:
    * <pre>
    *            /-- mObjs --* ObjTrans -- ObjModel
    * mRoot -- mView
    *            \-- mStaticObjs --* ObjTrans -- ObjModel
    * </pre>
    *
    * In this way we keep the movable objects as well as the static objects
    * separate from each player's view.
    */
   class Scene {
   public:
      Scene();
      ~Scene();

      void draw();

      /**
       * Inserts the given object into the scene at the root level. The scene
       * does not actually hold on to a pointer to the object, but rather adds
       * it's model to the SG.
       *
       * @param obj        the object to add
       */
      void addObject(const game::Object& obj);

      /**
       * Removes the given object from the scene.
       *
       * @param obj        the object to remove
       */
      void removeObject(const game::Object& obj);

      /**
       * Gets the tranform node that contains the given object's model.
       *
       * @param obj        the object whose node shall be retrieved
       *
       * @return  the transform node if found; NULL otherwise
       */
      osg::Transform* getNode(const game::Object& obj);

      void update(const game::Object& obj);

      /**
       * Gets the specialized camera we use.
       *
       * @return     this scene's camera
       */
      Camera& getCamera();

   private:
      /// Our view into the scene.
      osgUtil::SceneView* mSceneView;

      /// The root node in our scene
      osg::Group* mRoot;

      /// The tranform node representing the camera's transform.
      osg::Transform* mFollowView;

      /// Camera's position and orientation before follow adjustment
      osg::Transform* mFollowTarget;

      /// The group node containing all dynamic objects.
      osg::Group* mObjs;

      /// The group node containing all static objects.
      osg::Group* mStaticObjs;

      /// Manages and caches models loaded from disk.
      ModelManager mModelMgr;

      /// Our specialized camera into the scene.
      Camera mCamera;
   };
}
#endif

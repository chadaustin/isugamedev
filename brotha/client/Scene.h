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
 * Date modified: $Date: 2002-04-22 04:16:20 $
 * Version:       $Revision: 1.1 $
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

#include <osg/Matrix>
#include <osg/Transform>
#include <osgUtil/SceneView>
#include "ModelManager.h"

namespace client {
   /**
    * Manages our scene. The scene is initially set up as:
    * <pre>
    *      /-- mViews --* PlayerNView
    * mRoot
    *      \-- mObjs --* ObjTrans -- ObjModel
    *       \-- mStaticObjs --* ObjTrans -- ObjModel
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
       * Inserts the given object into the scene at the root level.
       *
       * @param node             the node to insert
       */
      void addObject(const std::string& name, const std::string& model);

      /**
       * Removes the object with the given name from the scene.
       */
      void removeObject(const std::string& name);

   private:
      /// Our view into the scene.
      osgUtil::SceneView* mSceneView;

      /// The root node in our scene
      osg::Group* mRoot;

      /// The group node containing all player views.
      osg::Group* mViews;

      /// The group node containing all dynamic objects.
      osg::Group* mObjs;

      /// The group node containing all static objects.
      osg::Group* mStaticObjs;

      /// Manages and caches models loaded from disk.
      ModelManager mModelMgr;
   };
}
#endif

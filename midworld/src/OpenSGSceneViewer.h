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
 * File:          $RCSfile: OpenSGSceneViewer.h,v $
 * Date modified: $Date: 2002-10-09 02:20:57 $
 * Version:       $Revision: 1.4 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_OPENSG_SCENE_VIEWER_H
#define MW_OPENSG_SCENE_VIEWER_H

#ifdef WIN32  // OpenSG needs Winsock  :(:(:(
#include <winsock.h>
#endif
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGMatrixCamera.h>
#include <OpenSG/OSGPassiveWindow.h>
#include <OpenSG/OSGPassiveViewport.h>
#include <OpenSG/OSGPassiveBackground.h>
#include <OpenSG/OSGTransform.h>
#include "SceneViewer.h"
#include "SpatialIndex.h"

namespace mw
{
   /**
    * OpenSG implementation of the SceneViewer interface.
    */
   class OpenSGSceneViewer : public SceneViewer, public SpatialIndex
   {
   public:
      OpenSGSceneViewer(Scene* scene);
      ~OpenSGSceneViewer();

      /**
       * Draws the scene into the current OpenGL context.
       */
      void draw();

      /**
       * Finds the rigid bodies whose bounds intersect the given region.
       *
       * @param region     the search region that bodies will be tested against
       *
       * @return  a list of intersecting bodies
       */
      std::list<RigidBody*> intersect(const gmtl::AABoxf& region);

      void entityAdded(const SceneEvent& evt);
      void entityRemoved(const SceneEvent& evt);

   private:
      void debugDrawBounds();

   private:
      Scene* mScene;

      /// A mapping of entity IDs to their respective node
      typedef std::map<Entity::UID, osg::NodePtr> EntityNodeMap;
      EntityNodeMap mEntityNodeMap;

      osg::RenderAction* mRenderAction;
      osg::PassiveWindowPtr mWin;
      osg::PassiveViewportPtr mViewport;
      osg::PassiveBackgroundPtr mBackground;
      osg::MatrixCameraPtr mCamera;

      osg::NodePtr mSceneRoot;
      osg::TransformPtr mSceneTransform;
   };
}

#endif

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
 * File:          $RCSfile: ModelManager.h,v $
 * Date modified: $Date: 2002-04-22 01:48:07 $
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
#ifndef CLIENT_MODEL_MANAGER_H
#define CLIENT_MODEL_MANAGER_H

#include <stdexcept>
#include <string>
#include <map>
#include <osgDB/ReadFile>

namespace client
{
   /**
    * OpenSceneGraph model manager. This class will try to load models from disk
    * and return a node containing that model. The model manager also does some
    * caching to improve loading speed.
    *
    * <h2>Example usage</h2>
    * \code
    *    ModelManager mgr;
    *    osg::Node* model = mgr.get("cessna.obj");
    *    myScene->addChild(model);
    * \endcode
    */
   class ModelManager
   {
   public:
      /**
       * Creates a new model manager with its own cache.
       */
      ModelManager();

      /**
       * Destroys this model manager and all the models it currently has loaded
       * and is managing.
       */
      ~ModelManager();

      /**
       * Loads the model from the disk if it's not already in the cache and
       * returns a pointer to the OSG node that contains the model. Note that
       * the ModelManager owns the memory to the returned node.
       *
       * @param model      the file containing the model description
       *
       * @return  the OSG node containing the model
       *
       * @throw std::exception      failed to load the model
       */
      osg::Node* get(const std::string& model);

   private:
      /**
       * Loads the model contained in the given file and returns the OSG node
       * that contains the model. This method does not check the cache.
       *
       * @param file    the file containing the model description
       *
       * @return  the OSG node containing the model
       *
       * @throw std::exception      failed to load the model
       */
      osg::Node* loadFile(const std::string& file) const;

   private:
      typedef std::map< std::string, osg::Node* > ModelCache;

      /// Our model cache map indexed by filename.
      ModelCache mCache;
   };
}

#endif

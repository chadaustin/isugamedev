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
 * File:          $RCSfile: ModelManager.h,v $
 * Date modified: $Date: 2002-10-09 08:09:39 $
 * Version:       $Revision: 1.4 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_MODEL_MANAGER_H
#define MW_MODEL_MANAGER_H

#include <string>
#ifdef WIN32  // OpenSG needs Winsock  :(:(:(
#include <winsock.h>
#endif
#include <OpenSG/OSGNode.h>

namespace mw
{
   /**
    * The ModelManager is responsible for loading 3D models from disk and
    * caching them for fast reuse. It is implemented such that all clients that
    * request the same model name will use the same model object to save on
    * memory usage.
    * 
    * <h3>Example: Using the ModelManager</h3>
    * \code
    *    // Create a new model manager
    *    ModelManager* mgr = new ModelManager();
    *
    *    osg::NodePtr* chaingun = mgr->get("models/chaingun.obj");
    *    osg::NodePtr* tree = mgr->get("models/tree.obj");
    *
    *    // Don't forget to free memory when we're done!
    *    delete mgr;
    * \endcode
    */
   class ModelManager
   {
   public:
      /**
       * Creates a new ModelManager.
       */
      ModelManager();

      /**
       * Destroys this ModelManager. Since all OpenSG models are refcounted,
       * this manager does not explicitly free any memory.
       */
      ~ModelManager();

      /**
       * Gets the root node of the graph for the model stored in the given file.
       *
       * @param model      the name of the file containing the model to load
       *
       * @return  the model's node; NULL if there was an error
       */
      osg::NodePtr get(const std::string& model);

      /**
       * Preloads the model stored in the given file and stores it in the cache
       * for later use.
       *
       * @param model      the name of the file containig the model to load into
       *                   the cache
       *
       * @return  true if the model was loaded successfully, false otherwise
       */
      bool preload(const std::string& model);

      /**
       * Removes all models contained in the cache.
       */
      void emptyCache();

   private:
      /**
       * Checks the cache for a model associated with the given name. If a model
       * is not in the cache, it is created. Otherwise, the model in the cache
       * is returned.
       *
       * Actually, a clone of the model's Node tree is returned that references
       * the same NodeCores.
       *
       * @param model      the name of the model to get
       *
       * @return  a model tree for the model, NULL if it could not be opened
       */
      osg::NodePtr getModel(const std::string& model);

   private:
      typedef std::map<std::string, osg::NodePtr> ModelCache;

      /// The cache of model names to the OpenSG subgraph
      ModelCache mCache;
   };
}

#endif

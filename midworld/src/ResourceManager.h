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
 * File:          $RCSfile: ResourceManager.h,v $
 * Date modified: $Date: 2002-09-17 10:33:08 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <string>
#include <map>

namespace mw
{
   /**
    * This class maps resource IDs to strings.
    */
   class ResourceManager
   {
   public:
      ResourceManager();
      ~ResourceManager();

      /**
       * Gets the string associated with the given resource identifier.
       *
       * @param resid   the ID of the resource to retrieve
       *
       * @return  the string value associated with the resource
       *
       * @throws  std::runtime_error if the resource ID is unknown
       */
      const std::string& get(const std::string& resid) const;

      /**
       * Adds the given resource into this manager such that the given value is
       * associated with the given resource ID.
       *
       * @param resid   the ID of the resource to add
       * @param value   the string value of the resource
       *
       * @throws  std::runtime_error if the resource ID is already in use
       */
      void add(const std::string& resid, const std::string& value);

      /**
       * Removes the resource with the given ID.
       *
       * @param resid   the ID of the resource to remove
       *
       * @throws  std::runtime_error if the resource ID is unknown
       */
      void remove(const std::string& resid);

   private:
      typedef std::map<std::string, std::string> ResourceMap;

      /// The map of resource IDs to their string.
      ResourceMap mResources;
   };
}

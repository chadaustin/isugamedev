/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/**************************************************************** siren-cpr beg
 *
 * siren - flexible 3D game engine
 * siren is (C) Copyright 2003 by members of the
 *    Iowa State University Game Developers Club
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
 * File:          $RCSfile: Singleton.h,v $
 * Date modified: $Date: 2003-02-03 02:54:35 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
#ifndef SIREN_SINGLETON_H
#define SIREN_SINGELTON_H

namespace siren
{
   /**
    * Templated singleton holder. This class will make any object a singleton.
    */
   template<class T>
   class Singleton
   {
   public:
      /**
       * Gets the singleton instance of the contained class.
       */
      static T& instance()
      {
         if (! mInstance)
         {
            mInstance = new T();
            atexit(destroySingleton);
         }
         return *mInstance;
      }

   private:
      /**
       * Destroys this singleton. This is called when the application is
       * terminated.
       */
      static void destroySingleton()
      {
         delete mInstance;
         mInstance = 0;
      }

   private:
      /// The singleton instance
      static T* mInstance;
   };

   template<class T>
   T* Singleton<T>::mInstance = 0;
}

#endif

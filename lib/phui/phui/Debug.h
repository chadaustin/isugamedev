/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/***************************************************************** phui-cpr beg
 *
 * phui - flexible user interface subsystem
 * phui is (C) Copyright 2002 by
 *      Chad Austin, Josh Carlson, Johnathan Gurley,
 *      Ben Scott, Levi Van Oort
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
 * File:          $RCSfile: Debug.h,v $
 * Date modified: $Date: 2005-01-25 01:41:59 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#ifndef PHUI_DEBUG_H
#define PHUI_DEBUG_H

#include <loki/Singleton.h>
#include <iostream>

namespace phui
{
   /**
    * Utility class for outputting messages to a stream.
    */
   class DebugImpl
   {
   public:
      
      /**
       * Default Constructor
       */
      DebugImpl()
         : mStream(&std::cout)
      {}

      /**
       * Sets the stream to use for output.
       *
       * @param   stream      the stream to use for outputting messages.
       */
      void setStream(std::ostream& stream)
      {
         mStream = &stream;
      }

      /**
       * Gets the Debug stream.
       *
       * @param   debug       true if debug output, false otherwise.
       */
      std::ostream& getStream(bool debug)
      {
         (*mStream) << "[phui]:";
         if (debug)
         {
            (*mStream) << "[DBG] ";
         }
         else
         {
            (*mStream) << "[ERR] ";
         }
         return *mStream;
      }

   private:

      /// the stream to use for outputting messages.
      std::ostream*        mStream;
   };

   typedef Loki::SingletonHolder<DebugImpl> Debug;

#define phuiDEBUG(cat) phui::Debug::Instance().getStream(cat)

static const bool phuiDBG_DEBUG = 1;
static const bool phuiDBG_ERROR = 0;

}

#endif

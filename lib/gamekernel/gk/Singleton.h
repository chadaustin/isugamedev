
//////////////////////////////////////////////////////////////////
//
//                         -=     Singleton     =-
//
// Definition: "restrict access to a class to one instance only."
//
/////////////////// <GK heading BEGIN do not edit this line> /////////////////
//
// gamekernel - a platform for running games
// gamekernel is (C) Copyright 2001-2002 by Kevin Meinert, Ben Scott
//
// Authors: Kevin Meinert <kevin@vrsource.org>
//          Ben Scott <bscott@iastate.edu>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the
// Free Software Foundation, Inc., 59 Temple Place - Suite 330,
// Boston, MA 02111-1307, USA.
//
// -----------------------------------------------------------------
// File:          $RCSfile: Singleton.h,v $
// Date modified: $Date: 2002-03-21 06:02:13 $
// Version:       $Revision: 1.8 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_SINGLETON_H
#define GK_SINGLETON_H

#include <gk/gkCommon.h>

namespace gk {

// you can use this coolio class to make a singleton,
// just inherit like so...
//
// class myClass : public kev::Singleton<myClass>
//
template< class singleClass >
class Singleton
{
public:
   // access your class with myClass::instance().
   inline static singleClass& instance( void )
   {

      static singleClass* the_instance1 = NULL;

      if (the_instance1 == NULL)
      {
         if (the_instance1 == NULL)
         { the_instance1 = new singleClass; }
      }
      return *the_instance1;

      //static singleClass the_instance1;
      //return the_instance1;
   }

protected:
   // dont create a singleton with new!
   // use instance()
   Singleton()
   {
   }

   // don't delete a singleton!
   virtual ~Singleton()
   {
   }
};

} // namespace gk

#endif


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
// File:          $RCSfile: DLLInterface.h,v $
// Date modified: $Date: 2002-03-18 05:39:33 $
// Version:       $Revision: 1.1 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_DLLINTERFACE_H
#define GK_DLLINTERFACE_H

#include "gk/gkCommon.h"
#include <iostream>

namespace gk {

   namespace Private {
      /**
       * Interfaces exposed across a DLL boundary should derive from this class
       * to ensure that their memory is released cleanly and safely. This class
       * should be used in conjunction with the DLLImpl template. <b>Your
       * interface should NOT define a destructor!</b>
       *
       * <h3>Example Usage</h3>
       * \code
       *    class MyInterface : public DLLInterface {
       *       //MyInterface method declarations here ...
       *    };
       * \endcode
       *
       * @see DLLImpl
       */
      class DLLInterface
      {
      protected:
         /**
          * Handles the destruction of this class. This is essentially a destructor
          * that works across DLL boundaries.
          */
         virtual void destroy() = 0;

      public:
         /**
          * Specialized delete that calls destroy instead of the destructor.
          */
         void operator delete( void* p )
         {
            std::cout<<"DLLInterface::delete"<<std::endl;
            if ( p )
            {
               DLLInterface* i = static_cast<DLLInterface*>(p);
               i->destroy();
            }
         }
      };

      /**
       * Implementations of interfaces across DLL boundaries that derive from
       * DLLInterface should derive from this template to ensure that their memory
       * is released safely and cleanly.
       *
       * <h3>Example Usage</h3>
       * \code
       *    MyImpl : public DLLImpl< MyInterface > {
       *       virtual ~MyImpl();
       *       // MyImpl method declarations here ...
       *    };
       * \endcode
       *
       * @see DLLInterface
       */
      template< class Interface >
      class DLLImpl : public Interface
      {
      public:
         virtual ~DLLImpl() { std::cout<<"~DLLImpl"<<std::endl;}

         /**
          * Implementation of DLLInterface's destroy method. This function will
          * make sure this object get's deleted in a polymorphic manner. You
          * should NOT reimplement this method.
          */
         virtual void destroy()
         {
            std::cout<<"DLLImpl::destroy"<<std::endl;
            delete this;
         }

         /**
          * Overloaded operator delete calls global operator delete since
          * DLLInterface modified this functionality to protect memory.
          *
          * @param p    pointer to the memory to delete
          */
         void operator delete( void* p )
         {
            std::cout<<"DLLImpl::delete"<<std::endl;
            ::operator delete( p );
         }
      };
   } // namespace Private
} // namespace gk

#endif

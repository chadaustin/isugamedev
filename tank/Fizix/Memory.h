
//////////////////////////////////////////////////////////////////
//
//                         -=     ani::Memory     =-
//
// Definition: "Base class for all DynamicSystem objects"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: Memory.h,v $
//    $Date: 2001-10-17 03:42:50 $
//    $Revision: 1.3 $
//    Copyright (C) 1998, 1999, 2000  Kevin Meinert, kevin@vrsource.org
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU Library General Public
//    License as published by the Free Software Foundation; either
//    version 2 of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Library General Public License for more details.
//
//    You should have received a copy of the GNU Library General Public
//    License along with this library; if not, write to the Free
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
///////////////// <auto-copyright END do not edit this line> ///////////////////
#ifndef aniREFERENCE_COUNTABLE_MEMORY
#define aniREFERENCE_COUNTABLE_MEMORY

// particle system memory...
namespace ani
{
   class Memory
   {
   public:
      Memory() : mInSystem( false ) {}
      virtual ~Memory() {}
      bool isInSystem() const { return mInSystem; }
      void isInSystem( bool setting ) { mInSystem = setting; }

   private:
      bool mInSystem;
   };

}; // namespace ani


#endif

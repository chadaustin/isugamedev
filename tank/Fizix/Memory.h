
//////////////////////////////////////////////////////////////////
//
//                         -=     ani::Memory     =-
//
// Definition: "Base class for all DynamicSystem objects"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: Memory.h,v $
//    $Date: 2001-10-10 12:39:00 $
//    $Revision: 1.2 $
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
#include <assert.h>

// (particle system memory at bottom of file...)...

// rip this out... (use shared_ptr)
namespace anii
{

   // basic memory...
   // you MUST call deref to delete, do not call delete!!!!!
   // TODO: hide new and delete somehow, since delete should never be used, 
   //       and new makes it tempting to call delete.
   // on creation, refcount == 0, so if you intend to own the memory created, you 
   // should ref it
   class Memory
   {
   public:
      enum States
      {
         BAD = -69,
      };
       //: default constructor
       // on creation, refcount == 0, so if you intend to own the memory 
       // created, you should ref it
      Memory();

       // on creation, refcount == 0, so if you intend to own the memory 
       // created, you should ref it
      Memory( const Memory& r ) : ___mNumTimesReferenced( 0 )
       {
          //dont copy ref number.
          //std::cout<<"alive\n"<<std::flush;
       }

   public:
       //: destructor
       // you MUST call checkDelete to delete, do not call delete!!!!!
       virtual ~Memory()
       {
          assert( ___mNumTimesReferenced != BAD && ___mNumTimesReferenced >= 0 && "this data has been dereferenced more times than referenced, someone is probably holding on to the data after they called deref(), or someone called deref too many times. also, make sure you use checkDelete, or unrefDelete." );
          ___mNumTimesReferenced = BAD;
          //std::cout<<"dead\n"<<std::flush;
       }

   public:
       Memory& operator=( const Memory& r )
       {
          //dont copy ref number.
          return *this;
       }

      //: increase the reference count by 1, return the new refcount
      const int& ref();

      //: decrease the reference count by 1, then call checkDelete
      // equivalent to calling Memory::unref followed by Memory::checkDelete
      // return true if deleted, false if not
      bool unrefDelete();

   public:
      //: decrease the reference count by 1, return the new refcount
      const int& unref();

      //: return the reference count
      const int& getRef() const;

      //: decrease the reference count by 1, return the new refcount
      const int& unrefGetRef();

      //: if refcount <= 0, then delete the memory
      //  if the object has any refcountable children, then they will
      //  have Memory::unrefDelete() called on them.
      // return true if deleted, false if not
      virtual bool checkDelete();

   private:
      mutable int ___mNumTimesReferenced;
   };

   //: default constructor
   inline Memory::Memory() : ___mNumTimesReferenced( 0 )
   {
      //std::cout<<"alive\n"<<std::flush;
   }

   //: get the reference count
   inline const int& Memory::getRef() const
   {
      assert( ___mNumTimesReferenced != BAD && "this data has been deleted, someone is probably holding on to the data after they called deref()" );
      return ___mNumTimesReferenced;
   }
   
   //: increase the reference count
   inline const int& Memory::ref()
   {
      assert( ___mNumTimesReferenced != BAD && "this data has been deleted, someone is probably holding on to the data after they called deref()" );
      ++___mNumTimesReferenced;
      //std::cout<<"ref: "<<this->getRef()<<"\n"<<std::flush;
      return this->getRef();
   }

   //: decrease the reference count.
   inline const int& Memory::unref()
   {
      assert( ___mNumTimesReferenced != BAD && ___mNumTimesReferenced >= 0 && "this data has been dereferenced more times than referenced, someone is probably holding on to the data after they called deref(), or someone called deref too many times. also, make sure you use checkDelete, or unrefDelete." );
      --___mNumTimesReferenced;
      //std::cout<<"unref: "<<this->getRef()<<"\n"<<std::flush;
      return this->getRef();
   }

   //: if refcount <= 0, then delete the memory
   //  if the object has any refcountable children, then they will
   //  have Memory::unrefDelete() called on them.
   // return true if deleted, false if not
   inline bool Memory::checkDelete()
   {
      assert( ___mNumTimesReferenced != BAD && ___mNumTimesReferenced >= 0 && "this data has been dereferenced more times than referenced, someone is probably holding on to the data after they called deref(), or someone called deref too many times. also, make sure you use checkDelete, or unrefDelete." );
      if (___mNumTimesReferenced <= 0)
      {
         delete this;
         return true;
      }
      else
      {
         return false;
      }   
   }
   
   //: decrease the reference count by 1, then call checkDelete
   // equivalent to calling Memory::unref followed by Memory::checkDelete
   // return true if deleted, false if not
   inline bool Memory::unrefDelete()
   {
      this->unref();
      return this->checkDelete();
   }

   //: decrease the reference count by 1, return the new refcount
   inline const int& Memory::unrefGetRef()
   {
      this->unref();
      return this->getRef();
   }


}; //namespace kev


// particle system memory...
namespace ani
{
   class Memory : public anii::Memory
   {
   public:
      Memory() : anii::Memory(), mInSystem( false ) {}
      virtual ~Memory() {}
      bool isInSystem() const { return mInSystem; }
      void isInSystem( bool setting ) { mInSystem = setting; }

   private:
      bool mInSystem;
   };

}; // namespace ani


#endif

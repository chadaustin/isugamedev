
//////////////////////////////////////////////////////////////////
//
//                  -=     Lookup oriented RTTI     =-
//
// Definition: "RTTI designed for function table lookups.
//              integer and string based rtti, untested...
//              unique integer id associated with every class
//              starts at zero and increments for each new class 
//              added during runtime"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: LookupRTTI.h,v $
//    $Date: 2001-10-10 20:05:29 $
//    $Revision: 1.1 $
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
#ifndef LOOKUP_RUN_TIME_TYPE_INFO
#define LOOKUP_RUN_TIME_TYPE_INFO

#define LOOKUPRTTI_DECLARE(className, parentClassName)                 \
public:                                                               \
  inline static const int& classID()                                  \
  {                                                                   \
    static int m##className##UniqueId = LookupRTTIstore::instance().genTypeID( parentClassName::classID() ); \
    return m##className##UniqueId;                                   \
  }                                                                   \
  inline virtual const int& getClassID() const                        \
  {                                                                   \
    return className::classID();                                     \
  }                                                                   \
  inline static const char* className() const                         \
  {                                                                   \
     return #className;                                              \
  }                                                                   \
  inline virtual const char* getClassName() const                     \
  {                                                                   \
     return className::className();                                  \
  }                                                                   \
                                                                      \
  LOOKUPRTTI_DECLARE_ROOT(className)                                   \
  inline virtual const int& getParentID() const                       \
  {                                                                   \
      return className::parentClassID();                             \
  }                                                                   \
                                                                      \
  inline static const int& parentClassID()                            \
  {                                                                   \
    return parentClassName::classID();                               \
  }

class LookupRTTIstore : public Singleton<LookupRTTIstore>
{
   LookupRTTIstore() : mTotal( 0 )
   {
   }

   // Get a new unique ID number each time.
   void setParent( int classid, int parentid )
   {
      if (classid > mParentLookupTable.size())
         mParentLookupTable.resize( classid );
      mParentLookupTable[classid] = parentid;
   }   
   int genTypeID( int parentid ) 
   { 
      static int junk = 0; 
      mTotal = junk; 
      junk++; 
      this->setParent( junk, parentid );
      return junk; 
   }
   int getNumTypes() { return mTotal; }
   int mTotal;
   std::vector<int> mParentLookupTable;
}

class LookupRTTI
{
public:
   LOOKUPRTTI_DECLARE( LookupRTTI, LookupRTTI ) //my parent is myself (no parent)
};



#endif

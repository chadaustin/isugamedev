
//////////////////////////////////////////////////////////////////
//
//                         -=     iniSection     =-
//
// Definition: ""
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: iniSection.h,v $
//    $Date: 2001-10-10 13:01:16 $
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
#ifndef INI_GROUP
#define INI_GROUP

#include <map>
#include "iniUtils.h"
#include "assert.h"

//: a group is a part of an ini file denoted by brackets, for example:
//       [person]
//       name = kevin
//       age = 24
//  where the group here is 'person'
class iniSection
{
public:
   //: read the key named "keyName"
   //  if key exists, then return the data value stored in that key, and return result=true
   //  if key does not exist, then return false
   void getKey( const std::string& keyName, std::string& keyData, bool& result ) const
   {
      if (mKeyDataPairs.count( keyName ) > 0)
      {
         result = true;
         std::map< std::string, std::string >::const_iterator it  = mKeyDataPairs.find( keyName );
         assert( (*it).first == keyName );
         keyData = (*it).second;
         return;
      } 
      
      result = false;
   }
   
   //: change an existing key named "keyName", 
   //  if key didn't exist, then this function will add one.
   void putKey( const std::string& keyName, const std::string& data )
   {
      mKeyDataPairs[ const_cast<std::string&>( keyName ) ] = data;
      
      iniUtil::addStringToVector( iniUtil::PUTUNIQUE, keyName, mKeysInOrder );
      assert( mKeysInOrder.size() == mKeyDataPairs.size());
   }

public:
   // output all data contained in this group
   // should be formatted the same as a normal syntactically correct ini file.
   void output( std::ostream& out, bool preserveorder ) const
   {   
      if (preserveorder == true)
      {
         this->outputOrderedKeys( out );
      }
      else
      {
         this->outputAlphabetizedKeys( out );
      }
   }

   // returns the number of keys in this section.
   int size() const { assert( mKeysInOrder.size() == mKeyDataPairs.size() ); return mKeyDataPairs.size(); }
   
protected:
   void outputAlphabetizedKeys( std::ostream& out ) const
   {
      std::map< std::string, std::string >::const_iterator it;
      
      // print out each section.
      for (it = mKeyDataPairs.begin(); it != mKeyDataPairs.end(); ++it)
      {
         out<<(*it).first.c_str()<<" = "<<(*it).second.c_str()<<"\n"<<std::flush;
      }
   }
        
   void outputOrderedKeys( std::ostream& out ) const
   {
      for ( int x = 0; x < this->size(); ++x)
      {
         std::string keyData;
         bool result;
         std::string keyName = this->keyName( x );
         this->getKey( keyName, keyData, result );
         assert( result == true );
         out<<keyName.c_str()<<" = "<<keyData.c_str()<<"\n"<<std::flush;
      }     
      out<<"\n"<<std::flush;
   }    
   // return the section's name by index.  
   // order is preserved within an ini file, so 0 should always return the first entry.
   // required: 0 <= index < this->size()
   // NOTE: use the result of this func in combination with getSection
   //     to get the sections in order of creation..
   const std::string& keyName( const int& index ) const
   { 
      assert( index < mKeysInOrder.size() && "section: if this fails, then your index is off the end" );
      assert( mKeyDataPairs.count( mKeysInOrder[index] ) != 0 && 
            "section: if this fails, then someone is not using the keepTrackOf function, or there is a major problem internal to the keepTrackOf system...");
      
      std::map< std::string, std::string >::const_iterator it  = mKeyDataPairs.find( mKeysInOrder[index] );
      assert( (*it).first == mKeysInOrder[index] && "make sure the key returned is the name we asked for, if fails, then stl has a bug..." );
      
      return (*it).first;
   }
   
private:
   struct ltstring
   {
     bool operator()( const std::string& s1, const std::string& s2) const
     {
       return strcmp( s1.data(), s2.data() ) < 0;
     }
   };
   std::map< std::string, std::string > mKeyDataPairs;
   std::vector< std::string > mKeysInOrder;
};

#endif

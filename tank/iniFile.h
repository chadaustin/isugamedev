
//////////////////////////////////////////////////////////////////
//
//                         -=     iniFile     =-
//
// Definition: ""
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: iniFile.h,v $
//    $Date: 2001-09-28 19:21:24 $
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
#ifndef INI_FILE
#define INI_FILE

#include "iniSection.h"
#include "iniUtils.h"

//: iniFile represents the structure of a standard MS Windows ini file
//  It is a hierarchy of:
//  + File
//    - Section
//      - Key (Name/Value pair)
//    - Section
//      - Key
//    - Section
//      - Key
//
//: ini file format
//  You can have infinite sections in a file, with infinite keys under each section.
//  Names should be unique, but if repeated, the last in the file 
//    will just overwrite any previously read values.
//  For example:  [person1]
//                name = kevin
//                age = 24
//                description = me
//
//                [person2]
//                name = terry
//                age = 24
//                description = milionth monkey
//
//                [person3]
//                name = allen
//                age = 24
//                description = golden child.
//
//: definitions
// 1.) File is a container for Group elements
//     It is the data.ini file itself
//
// 2.) Group is a container for Key elements.
//     Groups are only ever owned by Files
//     It is enclosed by brackets in the ini file format.
//     For example:  [person]
//                   name = kevin
//                   age = 24
//     where the section here is 'person'
//
// 3.) Key is a name/value pair 
//     keys are only ever owned by Groups
//     It is described with an '=' in the ini file format.
//     For example:   name = kevin
//                    age = 24
//  in this case, the name is 'name' and 'age', and the value is 'kevin' and '24'
class iniFile
{
public:
   //: read ini data from "filename"
   void load( const char* const filename );
   
   //: write ini data to filename, overwriting any previous file stored there.
   void save( const char* const filename, bool preserveorder = true )
   {
      mPreserveOrder = preserveorder;
      std::ofstream outputfile( filename, std::ios::out );
      if (outputfile.bad())
      {
         std::cout<< "The file could not be opened" << std::flush;
         return;
      }
      outputfile<<(*this);
      outputfile.close();
   }   
   
   void getSection( const std::string& sectionName, iniSection& section, bool& result ) const
   {
      if (mNamedSections.count( sectionName ) > 0)
      {
         result = true;
         std::map< std::string, iniSection >::const_iterator it  = mNamedSections.find( sectionName );
         assert( (*it).first == sectionName );
         section = (*it).second;
         return;
      }
      
      result = false;
   }   

   void putSection( const std::string& sectionName, const iniSection& section )
   {
      mNamedSections[ sectionName ] = section;
      
      iniUtil::addStringToVector( iniUtil::PUTUNIQUE, sectionName, mSectionsInOrder );
      assert( mSectionsInOrder.size() == mNamedSections.size() );
   }

   //: lookup a key value
   //  return the data in keyName
   //  given a sectionName and a keyName
   void getKey( const std::string& sectionName, const std::string& keyName, std::string& keyData, bool& result ) const
   {
      iniSection sec;
      this->getSection( sectionName, sec, result );
      if (result == false) return;
      sec.getKey( keyName, keyData, result );
   }   

   //: add a key value
   //  given a sectionName and a keyName
   // if section or key doesn't exist, then create them.
   void putKey( const std::string& sectionName, const std::string& keyName, const std::string& keyData )
   {
      iniSection& sec = mNamedSections[ sectionName ];
      sec.putKey( keyName, keyData );
      
      iniUtil::addStringToVector( iniUtil::PUTUNIQUE, sectionName, mSectionsInOrder );
      assert( mSectionsInOrder.size() == mNamedSections.size());
   } 

         
   // output preserves the order in which sections were added (or read from file)
   friend std::ostream& operator<<( std::ostream& out, const iniFile& inifile )
   {
      if (inifile.preserveOrder() == true)
      {
         inifile.outputOrderedSections( out );
      }
      else
      {
         inifile.outputAlphabetizedSections( out );
      }  
      return out;
   }
   
   // returns the number of sections in this inifile.
   int size() const { assert( mSectionsInOrder.size() == mNamedSections.size() ); return mNamedSections.size(); }
   
protected:
   // query whether operator<< preserves original order
   const bool& preserveOrder() const { return mPreserveOrder; }

   // return the section's name by index.  
   // order is preserved within an ini file, so 0 should always return the first entry.
   // required: 0 <= index < this->size()
   // NOTE: use the result of this func in combination with getSection
   //     to get the sections in order of creation..
   const std::string& sectionName( const int& index ) const
   { 
      assert( index < mSectionsInOrder.size() && "section: if this fails, then your index is off the end" );
      assert( mNamedSections.count( mSectionsInOrder[index] ) != 0 && 
            "section: if this fails, then someone is not using the keepTrackOf function, or there is a major problem internal to the keepTrackOf system...");
      
      std::map< std::string, iniSection >::const_iterator it  = mNamedSections.find( mSectionsInOrder[index] );
      assert( (*it).first == mSectionsInOrder[index] && "make sure the key returned is the name we asked for, if fails, then stl has a bug..." );
      
      return (*it).first;
      // return a reference to the section in the map.
      // sec = (*it).second;
   }
   

   void outputAlphabetizedSections( std::ostream& out ) const
   {
      std::map< std::string, iniSection >::const_iterator b;
      
      // print out each section.
      for (b = mNamedSections.begin(); b != mNamedSections.end(); ++b)
      {
         const std::string& name = (*b).first;
         const iniSection& sec = (*b).second;
         out<<"["<<name.c_str()<<"]\n"<<std::flush;
         sec.output( out, false );
      }
   }   

   void outputOrderedSections( std::ostream& out ) const
   {
      for ( int x = 0; x < this->size(); ++x )
      {
         iniSection sec;
         bool result;
         std::string name = this->sectionName( x );
         this->getSection( name, sec, result );
         assert( result == true );
         out<<"["<<name.c_str()<<"]\n"<<std::flush;
         sec.output( out, true );
      }
   }   
public:
   static void fromString( const std::string& str, int& i )
   {
      i = atoi( str.c_str() );
   }

   static void fromString( const std::string& str, float& f )
   {
      f = atof( str.c_str() );
   }

   static void toString( const float& f, std::string& str )
   {
      char buffer[ 1024 ];
      sprintf( buffer, "%f", f );
      str = buffer;
   }

   static void toString( const int& i, std::string& str )
   {
      char buffer[ 1024 ];
      sprintf( buffer, "%d", i );
      str = buffer;
   }

private:
   struct ltstring
   {
     bool operator()( const std::string& s1, const std::string& s2) const
     {
       return strcmp( s1.data(), s2.data() ) < 0;
     }
   };
   std::map< std::string, iniSection > mNamedSections;
   std::vector< std::string > mSectionsInOrder;
   
   bool mPreserveOrder;
};


//#include <alloca.h>
#include <iostream>

#include "regexx.hh"


void iniFile::load( const char* const filename )
{
   regexx::Regexx sectionMatcher, sectionNameMatcher;
   regexx::Regexx commentSubst;
   regexx::Regexx keyMatcher;
   std::string inifiletext;

   std::ifstream dataFile;
   dataFile.open( filename, std::ios::in );
   iniUtil::getAll( dataFile, inifiletext );
   dataFile.close();
   int num_of_matches;

   // remove comments...
   std::string nocomments;
   nocomments.reserve( inifiletext.size() );

   // remove all /* comments */
   nocomments = commentSubst.replace( inifiletext, "/[\\*]+[^{\\*/}]*[\\*]+/", "", regexx::Regexx::global);
   inifiletext = nocomments;
    
   // remove all // comments.
   nocomments = commentSubst.replace( inifiletext, "//[^\n]*", "", regexx::Regexx::global);
   inifiletext = nocomments;
    
   try
   {
      // divide the inifile into individual sections, each match should look like this:
      // [section]
      // key1 = value1
      // ...
      // keyn = valuen
      num_of_matches = sectionMatcher.exec( inifiletext,"\\[[^\\[]*", regexx::Regexx::global);

       for (int section = 0; section < sectionMatcher.match.size();  ++section)
       {
         std::string sectiontext = sectionMatcher.match[section];

         // extract the [sectionname] from the section.  
         // The match should be the name without the []
         // NOTE: couldn't figure out the stingy regex, 
         //       but the greedy one should work since there should only be one [] pair, 
         //       by definition of sectionMatcher regex.
         num_of_matches = sectionNameMatcher.exec( sectiontext, "\\[(.*)\\]", regexx::Regexx::global);
         std::string sectionname;
         if (num_of_matches != 0)
         { 
            sectionname = sectionNameMatcher.match[0].atom[0]; 
         } 
         else 
         { 
            sectionname = "--- not found: possible regex error?";
         }
         //         std::cout<<"Group: " << sectionname<<"\n"<<std::flush;

         // make sure that iniFile contains the section, 
         // NOTE: only useful if there are no keys, otherwise redundant.
         this->putSection( sectionname, iniSection() );
         
         // extract all the keys within the section
         // stips any whitespace before keyname, before and after =, and after the value.
         // i.e.     key name      =      value   string  
         //      becomes "key name" and "value   string"
         num_of_matches = keyMatcher.exec( sectiontext,"[ ]*([^=^\n]*[^=^ ^\n])[ ]*=+[ ]*([^\n]*[^ ^\n]?)[\n]*", regexx::Regexx::global);
         //       std::cout << "Found " << num_of_matches <<" entries:"<< endl;

         for (int key = 0; key < keyMatcher.match.size();  ++key)
         {
            const int keyStringIndex = 0, valueStringIndex = 1;
            //        std::cout << keyMatcher.match[entry].atom[key] << " = " << keyMatcher.match[entry].atom[value] << "\n"<<std::flush;

            std::string name = keyMatcher.match[key].atom[keyStringIndex];
            std::string data = keyMatcher.match[key].atom[valueStringIndex];
            this->putKey( sectionname, name, data );
         }
       }
   } // end of try
   catch(regexx::Regexx::CompileException &e) 
   {
       std::cerr << e.message().c_str() << std::endl;
   }

}

#endif

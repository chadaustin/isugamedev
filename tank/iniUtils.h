
//////////////////////////////////////////////////////////////////
//
//                         -=     iniUtil     =-
//
// Definition: ""
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: iniUtils.h,v $
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
#ifndef INIUTILITIES
#define INIUTILITIES

#include <vector>
#include <string>
#include <fstream>

class iniUtil
{
   public:
   static void getLine( std::ifstream& f, std::string& text  )
   {
      char buffer[2049];
      f.getline( buffer, 2048, '\n' );
      buffer[2048] = '\0';
      if (f.gcount() < 2048)
      {
         buffer[f.gcount()] = '\0';
      }
      text = buffer;
   }

   static void getAll( std::ifstream& f, std::string& buffer )
   {
	   //cout<<"Reading:["<<flush;
      while ((f.eof() == false) && (f.fail() == 0) )
      //while (f.gcount() >= 2048)
      {
	      //cout<<"."<<flush;
         char buf[2049];
         f.read( buf, 2048 );
         buf[2048] = '\0';
         if (f.gcount() < 2048)
         {
            buf[f.gcount()] = '\0';
         }
         buffer += buf;
      }
	   //cout<<"]\n"<<flush;
      //cout << "Gcount == " << f.gcount() << "\n"<<flush;
   }
   enum UniquifyOperation
   {
      PUTUNIQUE, REMOVE
   };
      
   //: perform an operation on a vector of strings:
   // PUTUNIQUE a name to a vector, if it doesn't already appear.
   static void addStringToVector( UniquifyOperation operation, const std::string& name, std::vector< std::string >& vec )
   {
      bool found = false;
      for (int x = 0; x < vec.size(); ++x)
      {
         if (vec[x] == name)
            found = true;
      }            
      // ADD a name to a vector, if it doesn't already appear.
      if (found == false)
      {
         vec.push_back( name );
      }
   }
   
   //: perform an operation on a vector of strings:
   // REMOVE a name from a vector
   static void removeStringFromVector( UniquifyOperation operation, const std::string& name, std::vector< std::string >& vec )
   {
      // rebuild the vector without any instances of name...
      std::vector<std::string> tempvec = vec;
      vec.clear();
      for (int x = 0; x < tempvec.size(); ++x)
      {
         if (tempvec[x] != name)
            vec.push_back( tempvec[x] );
      }            
   }
};

#endif
